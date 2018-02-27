#include <iostream>
#include "assign5.h"
#include "assignment6.h"
//using namespace std;

/***************************************************************
Function:public insert

Use: send integer to the private function

Parameters: one integer

Returns:Nothing

Notes:get the integer and send it to the private function with root included
***************************************************************/  
void BST::insert( int a)
{
  insert(root, a);
}

/***************************************************************
Function:private insert

Use: Insert an element in the binary tree

Parameters: the root of the tree and an integer

Returns:Nothing

Notes:Get the root and integer to insert. 
Check if the root is NULL if it is create a new NODE.
if element is less than root move left and call the function recursively,
do the same with an element thats greater and move right.
***************************************************************/
void BST::insert(Node*& ptr, int val) 
{   
   if (ptr == NULL)
   {
      ptr = new Node;
      ptr->data=val;
      ptr->left=NULL;
      ptr->right=NULL;
   }
  else
  {
    if (val < ptr->data)
      insert(ptr->left, val);
    else
      insert(ptr->right, val);    
  }
}

/***************************************************************
Function:private search

Use: send an integer to the private function

Parameters: one integer

Returns:boolean
Notes:send the root of the tree and return that function
***************************************************************/  
bool BST::search( int a)
{
    return search(root, a);
    
}

/***************************************************************
Function:private search

Use: check to see if an element exist within the tree

Parameters: one integer and root

Returns:Nothing

Notes:get and integer and search the tree for it. If found send return true.
check first if root is null if so then value DNE.
If root equals the value then return true and exit right away.
If neither had happen then move respectively if value is bigger or smaller.
and start the function again.
***************************************************************/  
bool BST::search(Node*& head, int val)
{
   
   if(head == NULL)
           return false;
   else if(head->data == val)
           return true;
   else
   {
       if(val < head->data)
             return search(head->left,val);
       else
             return search(head->right,val);
   }

   return false;  
} 

/***************************************************************
Function:public remove

Use: send integer to the private function

Parameters: one integer

Returns:boolean

Notes:get the integer and send it to the private function with root included
***************************************************************/  
bool BST::remove(int a)
{
    return remove(root, a);
}

/***************************************************************
Function:private remove

Use: remove an element from the tree

Parameters: one integer and root

Returns:boolean

Notes:First section will go to the desire node to remove.

the second part will remove the node and replace it with its predecessor.
to get the precedessor theres third fuction. saving the predecessor and then replacing it with the root.
***************************************************************/  
bool BST::remove(Node*& ptr, int val)
{
if (val < ptr->data)
return remove(ptr->left, val);
else if (val > ptr->data)
return remove(ptr->right, val);
else
return removeNode(ptr);
}


bool BST::removeNode(Node*& ptr)
{
int data;
Node *tempPtr = ptr;
if (ptr == NULL)
return false;
else if (ptr->right == NULL)
{
ptr = ptr->left; // Reattach the left child.
delete tempPtr;
return true;
}
else if (ptr->left == NULL)
{
ptr = ptr->right;
delete tempPtr;
return true;
}
// If the node has two children
else {
GetPredecessor(ptr->left, data);
ptr->data = data;
remove(ptr->left, data);
return true;
}


}

void BST::GetPredecessor(Node * ptr, int &data)
{
while (ptr->right != NULL)
ptr = ptr->right;
data = ptr->data;
}

/***************************************************************
Function:public sumLeftLeaves

Use: send root to the private functions

Parameters:

Returns:Int

Notes:send the root to the private functions
***************************************************************/  

int BST::sumLeftLeaves(){
    return sumLeftLeaves(root);
}

/***************************************************************
Function:private sumLeftLeaves

Use:add the left leaves of the tree

Parameters:root

Returns:Int

Notes:add all the left most leaves of the tree
***************************************************************/
int BST::sumLeftLeaves(Node*& root){

    int result = 0;
 
    if (root != NULL){
       if(root->left != NULL && root->left->left == NULL && root->left->right == NULL)
         result = result + root->left->data + sumLeftLeaves(root->right);
       else
         result = result + sumLeftLeaves(root->left) + sumLeftLeaves(root->right);
    }
 
    return result;
}
