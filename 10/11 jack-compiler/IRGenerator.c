class IRGenerator:
    def __init__(self, symbol_table):
        self.symbol_table = symbol_table
        self.instructions = []

    def generate(self, ast_node):
        method_name = f"gen_{ast_node.type}"
        generator = getattr(self, method_name, self.generic_gen)
        return generator(ast_node)

    def generic_gen(self, node):
        for child in node.children:
            self.generate(child)

    def gen_LetStatement(self, node):
        # Example: a = b + c
        # 1. generate IR for RHS expression
        rhs = self.generate(node.expr)
        # 2. generate IR for assignment
        self.instructions.append(f"{node.var_name} = {rhs}")

    def gen_Expression(self, node):
        # recursively generate IR for operands
        if node.is_binary_op():
            left = self.generate(node.left)
            right = self.generate(node.right)
            temp = self.new_temp()
            self.instructions.append(f"{temp} = {left} {node.op} {right}")
            return temp
        elif node.is_variable():
            return node.name
        elif node.is_constant():
            return node.value

    def new_temp(self):
        # returns a new temporary variable for IR
        if not hasattr(self, "_temp_counter"):
            self._temp_counter = 0
        temp = f"t{self._temp_counter}"
        self._temp_counter += 1
        return temp
