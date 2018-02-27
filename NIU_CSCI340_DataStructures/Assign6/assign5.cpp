#include "assign5.h"

/***************************************************************
Function: binTree

Use: Constructor

Parameters:  NON

Returns:NON

Notes:Creates an object binTree with the default Parameter root=NULL;
 
***************************************************************/
        binTree::binTree()
        {
          root = NULL;
        }
        
/***************************************************************
Function: insert  PUBLIC

Use: Insert value into Tree

Parameters:  Integer

Returns:Nothing

Notes:This is a public function to insert its use to keep the other
values private and not accesible.
 
***************************************************************/        
        void binTree::insert( int val )
        {
          insert(root,val);
        }
/***************************************************************
Function: height  PUBLIC

Use: get height for the tree

Parameters:  non

Returns:INT the height of the tree

Notes:This is a public function to height its use to keep the other
values private and not accesible.
 
***************************************************************/         
        unsigned binTree::height() const 
        {
          return(height(root));
        }
        
/***************************************************************
Function: size PUBLIC

Use: get size of the tree

Parameters:  Integer

Returns:Int the size of the tree

Notes:This is a public function to size its use to keep the other
values private and not accesible.
 
***************************************************************/         
        unsigned binTree::size() const 
        {
          return(size(root));
        }

/***************************************************************
Function: inorder PUBLIC

Use: display tree inorder method

Parameters:  pointer to a function

Returns:Nothing

Notes:This is a public function to inorder its use to keep the other
values private and not accesible.
 
***************************************************************/         
        void binTree::inorder( void(*display)(int) )
        {
          inorder(root , display);
        }

/***************************************************************
Function: preorder PUBLIC

Use: display tree in preorder method

Parameters:  pointer to a function

Returns:Nothing

Notes:This is a public function to preorder its use to keep the other
values private and not accesible.
 
***************************************************************/           
        void binTree::preorder( void(*display)(int) )
        {
          preorder(root , display);         
        }
        
/***************************************************************
Function: postorder PUBLIC

Use: display tree in postorder method

Parameters:  pointer to a function

Returns:Nothing

Notes:This is a public function to postorder its use to keep the other
values private and not accesible.
 
***************************************************************/           
        void binTree::postorder( void(*display)(int) )
        {
          postorder(root , display);
        }
        
        
        
        
        
/***************************************************************
Function: PRIVATE INSERT

Use: Insert a value to the tree

Parameters: Pointer and value

Returns:Nothing

Notes:Use the '&' to connect to the pointer.
Check if its NULL if it is create a new node with the value in parameters.
Let the right side and left be NULL since theyre new.

If there exist a pointer then check which size is bigger and send it to the smallest choice.
***************************************************************/           
        
        void binTree::insert( Node*& ptr, int val )
        {
          if (ptr == NULL) {
            ptr = new Node;
            ptr->right = NULL;
            ptr->left = NULL;
            ptr->data = val;
          }
          
          else if (size(ptr->right) < size(ptr->left))
            {
            insert(ptr->right, val);
            }
          else{

            insert(ptr->left, val);
            }
        }

/***************************************************************
Function: PRIVATE height

Use: Get the height of the tree

Parameters: A node pointer

Returns:int

Notes:Check if ptr is NULL to return the height of zero. 
Then check the lenght of the right side and then the left
compare both and return the highest.
***************************************************************/
        unsigned binTree::height( Node* ptr) const 
        {
          if (ptr==NULL) 
           return 0;
          else
          {
           /* compute the depth of each subtree */
           int lDepth = height(ptr->left);
           int rDepth = height(ptr->right);
 
           /* use the larger one */
           if (lDepth > rDepth) 
           return(lDepth+1);
           else return(rDepth+1);
         }
       }

/***************************************************************
Function: PRIVATE size

Use:get size of tree

Parameters: Pointer 

Returns:INT

Notes:Check the size of the tree. Check both sides and add them together plus one to count the default.
***************************************************************/        
        unsigned binTree::size( Node*ptr ) const 
        {
          if (ptr==NULL) 
            return 0;
          else    
            return(size(ptr->left) + 1 + size(ptr->right));
        }
   
/***************************************************************
Function: PRIVATE INORDER

Use: PRINT the tree in an inorder method

Parameters: Pointer to a function and a NODE pointer

Returns:Nothing

Notes: Go to the left all the way then move to the right use the display function to display elements
***************************************************************/        
	void binTree::inorder( Node* ptr, void(*display)(int) )
  {
    if (ptr != NULL)
    {
      inorder(ptr->left, display);
      display(ptr->data);
      inorder(ptr->right, display);
 }
  }
  
/***************************************************************
Function: PRIVATE preorder

Use: PRINT the tree in an preorder method

Parameters: Pointer to a function and a NODE pointer

Returns:Nothing

Notes:Move to element print and move left and print until null then go right.
Use the display function to display elements
***************************************************************/  
	void binTree::preorder( Node* ptr , void(*display)(int) )
  {
    if (ptr != NULL)
    {
      display(ptr->data);
      preorder(ptr->left , display);
      preorder(ptr->right , display);
    }
  }
  
/***************************************************************
Function: PRIVATE postorder

Use: PRINT the tree in an postorder method

Parameters: Pointer to a function and a NODE pointer

Returns:Nothing

Notes:Move  left and print from lowest to highest from left to right. Go right and do the same .
Use the display function to display elements
***************************************************************/    
	void binTree::postorder( Node* ptr, void(*display)(int) )
  {
    if (ptr != NULL)
    {
      postorder(ptr->left , display);
      postorder(ptr->right , display);
      display(ptr->data);
    }
  }