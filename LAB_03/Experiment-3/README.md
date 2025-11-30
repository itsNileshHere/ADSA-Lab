## Problem

This program converts an arithmetic expression from infix notation to postfix (Reverse Polish Notation) and then evaluates the resulting postfix expression.

## Theory

This program tackles two related problems in expression parsing:

1.  **Infix to Postfix Conversion:**
    *   **Infix Notation:** The common way we write mathematical expressions, where operators are placed between operands (e.g., `A + B`).
    *   **Postfix Notation (Reverse Polish Notation - RPN):** Operators follow their operands (e.g., `AB+`). Postfix expressions do not require parentheses and are easier for computers to evaluate using a stack.
    *   **Shunting-yard Algorithm:** This algorithm is commonly used for infix to postfix conversion. It uses a stack to temporarily hold operators and parentheses and an output queue (or string) for the postfix expression. It processes the infix expression token by token, applying rules based on operator precedence and associativity.

2.  **Postfix Evaluation:**
    *   Evaluating a postfix expression is straightforward using a stack.
    *   Operands are pushed onto the stack.
    *   When an operator is encountered, the required number of operands are popped from the stack, the operation is performed, and the result is pushed back onto the stack.
    *   The final result remains on the stack.

### Operator Precedence:
-   Higher precedence: `*`, `/`
-   Lower precedence: `+`, `-`
-   Parentheses `()` override precedence.

## Approach

The `InfixToPostfix_Evaluation.c` program uses a stack (implemented as a global character array `stack` and an integer `top` for managing stack operations) for both conversion and evaluation.

### Stack Operations:
-   `push(char c)`: Adds an element to the top of the stack.
-   `pop()`: Removes and returns the element from the top of the stack.
-   `peek()`: Returns the top element without removing it.
-   `isEmpty()`: Checks if the stack is empty.

### `infixToPostfix(char infix[], char postfix[])`:
1.  Initializes an empty operator stack.
2.  Iterates through the `infix` expression character by character:
    *   **Operand (digit):** Appends it directly to the `postfix` array.
    *   **'(':** Pushes it onto the operator stack.
    *   **')':** Pops operators from the stack and appends them to `postfix` until a matching '(' is found. The '(' is then popped (and discarded).
    *   **Operator:** Pops operators from the stack (and appends to `postfix`) that have higher or equal precedence than the current operator, until a lower precedence operator or '(' is encountered. Then, the current operator is pushed onto the stack.
3.  After processing the entire `infix` expression, any remaining operators on the stack are popped and appended to `postfix`.

### `evaluatePostfix(char postfix[])`:
1.  Initializes an empty operand stack (`valStack`).
2.  Iterates through the `postfix` expression character by character:
    *   **Operand (digit):** Converts the character digit to its integer value and pushes it onto `valStack`.
    *   **Operator:** Pops the top two operands (`op2` then `op1`) from `valStack`. Performs the arithmetic operation defined by the operator. Pushes the result back onto `valStack`.
3.  The final result of the evaluation is the single element remaining on `valStack`.

### `main()`:
-   Defines a sample `infix` expression.
-   Calls `infixToPostfix()` to convert it.
-   Prints the resulting `postfix` expression.
-   Calls `evaluatePostfix()` to evaluate the `postfix` expression.
-   Prints the evaluation result.

## Usage

To compile and run the code:

```bash
gcc InfixToPostfix_Evaluation.c -o InfixToPostfix_Evaluation
./InfixToPostfix_Evaluation
```

The `infix` expression is hardcoded in the `main` function. 