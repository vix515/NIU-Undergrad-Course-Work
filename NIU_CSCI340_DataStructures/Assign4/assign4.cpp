
#include "assign4.h"
#include <stack>

/***************************************************************
Function: empty

Use: Check is stacks are empty

Parameters: None

Returns: Boolean

Notes: Just check if the stacks are empty is so return true 
***************************************************************/
bool Queue::empty() const
{
	if(s1.empty() and s2.empty())
		return true;
	else
		return false;
}

/***************************************************************
Function: size

Use: check size of queue

Parameters: none

Returns: Int

Notes: Add the sizes of the two stacks and added to get the size of queue
***************************************************************/
int Queue::size() const
{
  int size = 0;
  if(!s1.empty())
    size = s1.size();
  if(!s2.empty())
    size = size + s2.size();
    
  return size;
}

/***************************************************************
Function: front

Use: check what number is in the front

Parameters: None

Returns: int

Notes: since stacks are the opposite of queue, we put a stack
"upsidedown" to convert it to a queue and then get the queue top.
After that we return the stack to normal position 
***************************************************************/
int Queue::front()
{
  int a = 0;
  
  if(s2.empty()){
    while(!s1.empty()){
      s2.push(s1.top());
      s1.pop();
    }
   a = s2.top();
    while(!s2.empty()){
      s1.push(s2.top());
      s2.pop();
    }
  }
    return a;
}

/***************************************************************
Function: back

Use: Returns the queue last item

Parameters: None

Returns: Int

Notes: Since queue and stakcs are opposites the back of a queue is the front of a stack
***************************************************************/
int Queue::back()
{
    return s1.top();
}

/***************************************************************
Function: push

Use: Push a number to the queue

Parameters: a conts int 'val'

Returns: Nothing

Notes: push the val into the main stack 's1' 
***************************************************************/
void Queue::push(const int& val)
{
  s1.push(val);
}

/***************************************************************
Function: pop

Use: pop the first number of a queue

Parameters: None

Returns: int

Notes: since stacks are the opposite of queue, we put a stack
"upsidedown" to convert it to a queue and then we pop the value.
After that we return the stack to normal position 
***************************************************************/
void Queue::pop()
{
   if(s2.empty()){
    while(!s1.empty()){
      s2.push(s1.top());
      s1.pop();
    }
   s2.pop();
    while(!s2.empty()){
      s1.push(s2.top());
      s2.pop();
    }
   }
}

