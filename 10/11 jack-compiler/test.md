## SECTION 1 — CONCEPTUAL (FOUNDATIONS)

**Q1.** What problem does the **tokenizer** solve that the parser should *not* solve?

**Q2.** Why is it incorrect to generate VM code inside the tokenizer?

**Q3.** Explain the difference between:
****
* syntax
* semantics

**Q4.** Why does Project 10 output XML instead of VM code?

**Q5.** What would break if the symbol table did not reset at the start of each subroutine?

---

## SECTION 2 — TOKENIZER (LEXICAL ANALYSIS)

Given this Jack code:

```jack
let sum = a + 10;
```

**Q6.** List the tokens **in order**, with their **token type**.

---

**Q7.** Why is `"Hello World"` a **single token**, but `Hello World` is not?

---

**Q8.** What happens if the tokenizer sees this?

```jack
/* comment starts
   comment never ends
```

What *should* a correct tokenizer do?

---

**Q9.** Is `_count123` a valid identifier? Why?

---

## SECTION 3 — PARSER (GRAMMAR & STRUCTURE)

**Q10.** Which component understands that this is invalid Jack?

```jack
class { Main }
```

Tokenizer or Parser? Why?

---

**Q11.** Match each parser function to its responsibility:

| Function              | Responsibility |
| --------------------- | -------------- |
| `compileExpression()` | ?              |
| `compileClass()`      | ?              |
| `compileTerm()`       | ?              |
| `compileStatements()` | ?              |

---

**Q12.** Why does Jack use a **recursive-descent parser** instead of a table-driven LR parser?

---

**Q13.** What grammar rule causes recursion here?

```jack
(a + (b * c))
```

---

## SECTION 4 — XML OUTPUT (PROJECT 10)

Given:

```jack
return x + 1;
```

**Q14.** Which XML tags must appear (order matters)?

---

**Q15.** Why is XML considered a **debug artifact**, not a compiler output?

---

## SECTION 5 — SYMBOL TABLE (SEMANTIC ANALYSIS)

Given:

```jack
class Test {
    field int x;
    static boolean flag;

    function void f(int a) {
        var int x;
        return;
    }
}
```

**Q16.** Fill the symbol table entries:

### Class scope

| Name | Type | Kind | Index |
| ---- | ---- | ---- | ----- |
| x    | ?    | ?    | ?     |
| flag | ?    | ?    | ?     |

### Subroutine scope (`f`)

| Name | Type | Kind | Index |
| ---- | ---- | ---- | ----- |
| a    | ?    | ?    | ?     |
| x    | ?    | ?    | ?     |

---

**Q17.** When `x` is used inside `f`, which `x` is referenced? Why?

---

**Q18.** What VM segment corresponds to each kind?

| Kind   | VM Segment |
| ------ | ---------- |
| field  | ?          |
| static | ?          |
| arg    | ?          |
| var    | ?          |

---

## SECTION 6 — VM STACK & MEMORY MODEL

**Q19.** What does this VM code do?

```vm
push constant 7
push constant 3
sub
```

---

**Q20.** After execution, where is the result stored?

---

**Q21.** Why does this code NOT store anything permanently?

```vm
push constant 5
```

---

## SECTION 7 — VMWRITER MAPPING

Translate to VM (assume `x` is `local 0`):

```jack
let x = x + 1;
```

**Q22.** Write the exact VM code.

---

**Q23.** Why does `do foo();` require a `pop temp 0`?

---

## SECTION 8 — CONTROL FLOW

Translate to VM (high-level logic is enough):

```jack
while (x < 10) {
    let x = x + 1;
}
```

**Q24.**

* How many labels are needed?
* Why?

---

**Q25.** What happens if you forget to negate the condition in `while`?

---

## SECTION 9 — FUNCTION CALLS & EXECUTION

Given:

```jack
do Output.printInt(5);
```

**Q26.**

1. How many arguments?
2. What VM command performs the call?
3. Where does the return value go?

---

**Q27.** Why must a function declare its number of local variables in VM?

---

## SECTION 10 — FULL PIPELINE (CRITICAL)

**Q28.** Put these in exact execution order:

* VM Emulator
* Symbol Table
* Tokenizer
* Parser
* VMWriter
* Screen output

---

**Q29.** Does the compiler ever execute the program? Explain.

---

**Q30.** Why does nothing “run in reverse” after output appears?

---

## SECTION 11 — DEBUGGING & FAILURE MODES

**Q31.** If your VM code is correct but the program crashes, where is the bug most likely?

---

**Q32.** If variables overwrite each other, which component is probably wrong?

---

**Q33.** If expressions evaluate incorrectly, name **two possible causes** in the compiler.

---

## SECTION 12 — FINAL DEEP QUESTION (NO BS)

**Q34.** In one paragraph, explain how **meaning** emerges from raw characters in a Jack file until pixels appear on the screen.

