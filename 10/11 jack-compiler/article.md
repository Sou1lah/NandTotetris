---
source: https://medium.com/@pextonjack/how-i-built-a-compiler-and-how-you-can-too-c9642994d0a0
---

A few months ago, I decided to build something I had no 
business building: a compiler.

Many of you have probably used one. When you click ‘run’ in VS Code, or ‘build’ in Unity, a compiler works behind the scenes to turn the code you’ve written into instructions a CPU can actually execute. But under the hood, they’re complex and notoriously full of pitfalls.

Yet, they’re also one of the most fascinating projects you can take on as a programmer. Building a compiler lets you explore how the abstraction layers, from machine code up to high-level code, actually work, and lets you construct a program that traverses those very abstraction layers yourself.

So, here’s how I went from an empty Visual Studio project to a working, albeit a toy, compiler that generates ARM64 assembly, and how you can follow a similar path.

## Why a compiler?

The reason I chose to make a compiler was actually because I wanted to learn how to write assembly code, and once I started writing ARM64, I thought to myself “Oh wow, I can see exactly how a high-level statement translates into this!” But anyone could want to make a compiler for any reason: familiarity with assembly, understanding design choices in compilers, or simply just for fun. And it’s a more structured systems-level project than writing raw assembly code, or making your own operating system.

If you’re not too interested in the systems aspect, and just want to translate your own language into something that’s runnable, you’d be better off writing an interpreter rather than a compiler, like the way Python is executed. With an interpreter, your code isn’t converted to assembly. It’s executed by a runtime that manages instructions without emitting assembly first. This is a much simpler task, so it’s understandable to start there first. But if you do want to write an interpreter instead of a compiler, then this is not the article for you. Instead, I’d suggest you check out [Bob Nystrom’s book on writing an interpreter](https://craftinginterpreters.com/introduction.html).

## Breaking down the problem

But how exactly does a compiler convert high-level code into assembly? The answer is an entire pipeline, which I’ll explain below. For this example, it’s quite light and is intended for toy compilers, rather than fully fledged compilers, meaning that specific or complex details won’t be discussed here.

In my implementation, each stage lives in its own C# class. This means that there’s a clear structure where each stage feeds into the next, from start to finish.

Additionally, I’ll preface this by saying that my first version was very basic. It only supported a single data type, 32-bit integers, which is part of what makes it so basic. And I recommend you don’t try to go too complex for your first attempt either.

### Lexing

The first step is to take your source code, and tokenise it to form a list of tokens. Each token will be quite basic, with just the type of token and the raw ‘lexeme’ (the string of what was tokenised in that token). For example, the statement `int x = 3;` would be split into `[Ident: "int"], [Ident: "x"], [Assignment: "="], [Int literal: 3]`. Notice how `int` is treated like an identifier (`Ident` for short), instead of being saved as an integer data type token. This is a style choice, and it doesn’t really matter whether you treat it as an identifier until parsing, or in lexing.

The reason the choice doesn’t matter is because the lexer is supposed to be “dumb.” It’s fast, and doesn’t try to understand what the code is saying yet. That’s the job of the parser.

My lexer approach was to iterate through every character of the original source code, checking whether it signified the start of a new token (if the character was a digit, then it represented a literal; if the character was an ASCII letter or underscore, then it represented the start of an identifier; if the character was punctuation or an operator, then it was treated as such). A key note is that the lexer should generally ignore spaces and newlines so programs parse the same with or without them

Here’s a snippet of what I did, in C#:

```c
for (int i = 0; i < code.Length;)
{

    // 1. Whitespace, line endings
    if (code[i] == ' ')
    {
        i++;
        column++;
        continue;
    }
    if (code[i] == '\n')
    {
        i++;
        line++;
        column = 1;
        continue;
    }

    // 2. Idents
    if (IsIdentStart(code[i]))
    {
        int start = i;

        while (char.IsAsciiLetterOrDigit(code[i]))
        {
            i++;
        }

        string ident = code.Substring(start, i - start);

        TokenType identType = CheckKeyword(ident);
        Token t = new(identType, ident, line, column);
        column += i - start;

        tokens.Add(t);

        continue;
    }
    // [...rest of checks]
}
```

Once the lexer detects the start of an identifier, it will keep iterating forwards until it reaches the end of the identifier. Then it adds the token to the list and continues.

Notice how each token is a class. The same could be achieved with a struct, but the main point is that it lets you store additional information alongside the lexeme and type, like line and column, while making it easier for future-you, rather than just using tuples.

### Parsing

Parsing is where the compiler takes the flat list of tokens from lexing and arranges them into a structured tree, known as an Abstract Syntax Tree (AST), which reflects the program’s meaning. In my case, I started with a simple if-else ad hoc parser, and then built onto a recursive-descent design. I’d recommend reading up on how to implement a recursive-descent parser if you get to it, but to start with, if-else statements are more than enough.

Here’s a sample of source code in my language:

```c
x: Int32 = 3;
y: Int32 = x * 2;
Output(y);
```

And what that would look like when converted to an AST, in a graphical form:

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*416Ec18uixO5ffcgizTDtQ.png)

A visualised AST, as it might look like internally in my implementation. Created with Microsoft Visio.

### Intermediate Representation (IR)

Intermediate Representation (IR) is a halfway house between high-level code and assembly. It’s quite abstract, and not platform-specific, but it’s also quite far away from the original source code.

This is where you take your AST and convert it into IR statements. There’s a wide range of IR designs, but I chose to use Tuple IR. This means that each instruction is atomic, and can’t be split any further without diving into assembly-like syntax.

Consider the following:

```c
x: Int32 = a + b * c;
```

This might be converted into Tuple IR like this:

```c
(MULTIPLY, b, c, t0)
(ADD, a, t0, t1)
(DECLARE, x, Int32, t1)
```

Of course, this is also something you can choose to design however you like. It’s your project, after all.

### Code generation

This part is either the easiest, or the hardest, depending on your familiarity with assembly. But essentially, you’re just taking the IR you generated in the previous step, and turning it into assembly code. And if you wrote your IR well, it should be almost 1:1, with maybe 2 or 3 instructions per IR instruction for the more complex structures like variable loading and storing.


I’d recommend first learning an assembly language before you get started. My choice was ARM64, with ELF formatting (the standard on Linux). [This was the guide I used to learn ARM64](https://mariokartwii.com/armv8/). Once you’ve learned an assembly language, you should intuitively understand how your IR instructions can be converted to assembly.

Alternatively, you can skip code generation altogether, and keep your IR as the lowest you go, especially if you never intended to produce a working compiler and just wanted to learn how one works. In this case, there’s no need to develop a code generation stage, although you might still want to make one that converts your IR into readable text.

## Design decisions

I chose to make my compiler simple. Primarily because it was meant to serve as a learning experience, but also because I knew that starting from nothing and trying to replace Clang would have been a waste of time.

Decisions like only supporting Int32 in my first version, or an ad hoc series of if-else statements instead of a real parser, were compromises I made to get it to output assembly as soon as it could, instead of getting bogged down by the technical details.

### Implementation language

I personally chose C#, because of its object-oriented nature, which made it easy to model each stage as a class. However, you could really write it in any high-level language you like. Especially since it’s a compiler, you could write it in Python, because compile-time performance isn’t critical for a learning project, only how long it takes for the compiled program to run (which would be the same no matter which language you wrote the compiler in).

### Source language design

This one is tougher. I personally designed my own language, ‘RISClet’, which was modelled after a mix of C and Swift. For example, here’s a sample:

```c
x: Int32 = 3;
y: Int32 = x / 3;
print(y);
```

But to be honest, how you choose to design your language doesn’t really matter. What matters is whether you’re consistent, and you don’t make big changes halfway through the project in how your language looks. I’d recommend drafting a document outlining the grammar of your language, which is especially helpful if you end up using third-party parsers instead of writing your own.

### Code generation choices

I won’t get too deep into this, because this is much more technical, and won’t matter unless you choose to compile to a real assembly language. But I chose to use ARM64 in the ELF format, which meant I could run it on Linux and use Linux system calls (syscalls). I chose ELF because it‘s the most obvious and well-known choice.

For memory allocation, I chose to use static memory allocation, instead of using dynamic memory allocation with functions like malloc from libc. Part of this was so that I could avoid linking to libc, and instead write my own libraries.

These choices made my binaries much more lightweight, which meant that the resulting binaries were often 5× smaller than equivalent dynamically-linked libc binaries, and 1000× smaller than equivalent statically-linked libc binaries (my own binaries were statically compiled for ARM64 ELF with custom hand-written libraries and no libc; “equivalent” means ‘equivalent in functionality’, and size is based on size-on-disk). Of course this came at a versatility trade-off, but that’s acceptable for learning projects.

### Practical considerations

When testing my compiler, I ran the compiled binaries inside a UTM (QEMU) virtual machine running Ubuntu Linux. I recommend doing something similar unless your computer’s operating system and architecture already match your compilation target, or if you’re not targeting a real assembly language at all. Using a VM is especially helpful if you want to experiment without risking changes to your main system.

![](https://miro.medium.com/v2/resize:fit:640/format:webp/1*p1D3R4kvkMkczd3AErx6TQ.png)

Output from a compiled Fibonacci program running in a Ubuntu virtual machine

## What went wrong

The biggest mistakes were actually the tiniest ones. If-statements in the wrong order that meant that suddenly loading variables turned into loading the value `0` into registers; bad mental arithmetic that meant that my results from arithmetic operations were overwriting each other; I could go on.

The lesson I learned here is to test every stage of the pipeline once you’ve written it. Even if it just outputs the half-complete IR or string of tokens, if you can trace exactly which stage things are going wrong in, it makes it much easier than poring over code dumps of ARM64 to understand how that zero got there.

## Why you should try it

Let’s be real: if you’re reading this article, chances are you’re not trying to write the next LLVM or Clang. You’re reading this article because you’ve never written a compiler before, and you want to try it out. And here’s why you should totally try it:

- It’s a brand-new experience to be working with both assembly code and high-level code simultaneously.
- It lets you appreciate the complexity of modern compilers, and how much heavy lifting they do behind the scenes.
- It helps you understand how the choices you make when writing your high-level code affect how it runs down to the silicon, helping you become a better programmer.
- It lets you appreciate the simplicity of writing high-level code!

## Getting started without breaking your brain

The best way to start is to start small, like I did. No functions, no if-statements, one data type, and basic arithmetic operations. Oh, and `print ` statement support. Then, you can slowly add features. And the best part is, if you wrote each stage to be compatible with the other stages, you can modify each stage one at a time, and you should still be able to compile old code that the other untouched stages originally supported. That’s part of what makes the decomposed pipeline structure work so well.

Make sure to work in small stages, developing each stage of the pipeline one-at-a-time instead of all at once, but also don’t try to make each stage of the pipeline fully-fledged before you’ve even gotten started on the next stage.

If you’re not sure how to write assembly, I’d suggest trying to compile to a simple assembly language, especially one that does the heavy lifting. Or even better, you could make your own pseudo-assembly language, inspired from real assembly languages, and then trace through the pseudo-assembly you output. That way, you can understand whether the rest of your pipeline works, without needing to learn actual assembly.

## My takeaways

Building a compiler taught me more about systems-level computing than any class I took in high school ever did. It gave me the confidence to dive into low-level problems that once seemed impossibly complex.

If you’ve ever wondered what happens between your code editor and the CPU, try writing a compiler. Even if you never ship it, you’ll come out as a better programmer.

## Source code

Unfortunately, since I’m submitting this project for the coursework component of a qualification, I can’t share the source code at the moment. I’ll publish an update once it’s available, which should be around mid-2026.
