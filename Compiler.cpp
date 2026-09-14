PS C:\Users\USER\CLionProjects\Compiler> .\main test.txt
Source is: 
if(x>5){
    return x;
    return 10;
    return x + y * 2;
}


IF
LEFT_PAREN
IDENTIFIER
BIGGER_THAN
INT_LIT
RIGHT_PAREN
LEFT_BRACE
RETURN
IDENTIFIER
SEMICOLON
RETURN
INT_LIT
SEMICOLON
RETURN
IDENTIFIER
PLUS
IDENTIFIER
MULTIPLY
INT_LIT
SEMICOLON
RIGHT_BRACE
END_OF_FILE
END_OF_FILE
End Of File Reached!!
Program
  IfStatment
    Condition
      BinaryNode: >
        IdentifierNode: x
        LiteralNode: 5
    ThenBranch
      Block
        ReturnStatment
          IdentifierNode: x
        ReturnStatment
          LiteralNode: 10
        ReturnStatment
          BinaryNode: +
            IdentifierNode: x
            BinaryNode: *
              IdentifierNode: y
              LiteralNode: 2

Duration is: 1136
PS C:\Users\USER\CLionProjects\Compiler> 
