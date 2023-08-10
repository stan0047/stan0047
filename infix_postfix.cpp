#include <iostream>
#include <string.h>
using namespace std;
#define MAX 30

char a[MAX]; // As the expression contains operators & operands, use a char array
int top;

void init()
{
  top = -1;
}
void push(char data)
{
  top++;
  a[top] = data;
}
char pop()
{
  if (top != -1)
  {
    int x = a[top];

    top--;
    return x;
  }
  else
    return ('\0');
}
int priority(char data)
{
  if (data == '*' || data == '/' || data == '%')
    return 3;
  else if (data == '-' || data == '+')
    return 2;
  else if (data == '>' || data == '<')
    return 1;
  else
    return 0;
}

int main()
{
  int len, j, k = 0;
  char opr;
  string s, post;
  cout << "enter the infix expression to be converted\n";
  getline(cin, s); // a  *b+c     7-3
                   //  01234
  len = s.length();
  init();

  for (j = 0; j < len; j++) // this loop is to process the characters of the entire expression one by one
  {
    if ((s[j] == ' ') || (s[j] == '\t')) // to ignore unwanted spaces left in between the characters of the expression
      continue;
    else if ((isdigit(s[j])) || (isalpha(s[j]))) // this condition will evaluate to true for an operand
    {                                            // an operand can be a digit or alphabet and so simply add it to
      post.append(1, s[j]);                      // post string
    }
    else if (s[j] == '(') // if character is '(' push it onto the stack
      push(s[j]);
    else if (s[j] == ')') // if character is ')'
    {
      do
      {
        opr = pop();    // pop the next character from the top of stack
        if (opr == '(') // if popped character is '(' simply ignore
          break;
        else
          post.append(1, opr); // else append the popped character to post string
      } while (opr != '(');    // the above steps are repeated till an '(' is encountered.
    }
    else // this 'else' part will handle operators
    {
      if (top == -1) // if stack is empty, simply push the current character (which is an operator)
        push(s[j]);  // on to the stack
      else
      {
        opr = pop();
        if (opr == '(')
        {
          push(opr);
          push(s[j]);
        }
        else
        {                                         // otherwise pop the topmost operator (opr) and compare priority of 'opr' with
          while (priority(opr) >= priority(s[j])) // priority of current operator. If priority of opr is higher, append it
          {                                       // to post string and repeat the 'pop' & 'compare' operations till
            post.append(1, opr);                  // the popped character 'opr' has a lesser priority than that of curren                               // operator (c[j]) or till the stack becomes empty
            opr = pop();
            if (opr == '\0')
              break;
          }
          push(opr);  // else if priority of popped character 'opr' is lesser than that of current
          push(s[j]); // operator,we should push the current operator onto stack. But before that
        }
      } // we should also push the operator that we popped for comparison
    }   // Hence two 'push' statements
  }     // at the end of this 'for' loop entire expression would have been processed.
  char x;
  do // at last pop the remaining contents from the stack and append them to post string
  {
    x = pop();
    if (x != '\0')
      post.append(1, x);
  } while (x != '\0');
  post.append(1, '\0'); // also add a NULL character at the end of 'post' string
  cout << post;
  return 0;
}