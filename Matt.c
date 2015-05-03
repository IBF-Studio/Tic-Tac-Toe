#include<stdio.h>
#include<stdlib.h>

int sum = 0;

typedef struct treeNode
{
	int data;
	struct treeNode *left;
	struct treeNode *right;

}treeNode;

treeNode* FindMin(treeNode *node)
{
	if (node == NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if (node->left) /* Go to the left sub tree to find the min element */
		return FindMin(node->left);
	else
		return node;
}
treeNode* FindMax(treeNode *node)
{
	if (node == NULL)
	{
		/* There is no element in the tree */
		return NULL;
	}
	if (node->right) /* Go to the left sub tree to find the min element */
		FindMax(node->right);
	else
		return node;
}

treeNode * Insert(treeNode *node, int data)
{
	if (node == NULL)
	{
		treeNode *temp;
		temp = (treeNode *)malloc(sizeof(treeNode));
		temp->data = data;
		temp->left = temp->right = NULL;
		return temp;
	}

	if (data >(node->data))
	{
		node->right = Insert(node->right, data);
	}
	else if (data < (node->data))
	{
		node->left = Insert(node->left, data);
	}
	/* Else there is nothing to do as the data is already in the tree. */
	return node;

}

treeNode * Delete(treeNode *node, int data)
{
	treeNode *temp;
	if (node == NULL)
	{
		printf("Element Not Found");
	}
	else if (data < node->data)
	{
		node->left = Delete(node->left, data);
	}
	else if (data > node->data)
	{
		node->right = Delete(node->right, data);
	}
	else
	{
		/* Now We can delete this node and replace with either minimum element
		in the right sub tree or maximum element in the left subtree */
		if (node->right && node->left)
		{
			/* Here we will replace with minimum element in the right sub tree */
			temp = FindMin(node->right);
			node->data = temp->data;
			/* As we replaced it with some other node, we have to delete that node */
			node->right = Delete(node->right, temp->data);
		}
		else
		{
			/* If there is only one or zero children then we can directly
			remove it from the tree and connect its parent to its child */
			temp = node;
			if (node->left == NULL)
				node = node->right;
			else if (node->right == NULL)
				node = node->left;
			free(temp); /* temp is longer required */
		}
	}
	return node;

}

treeNode * Find(treeNode *node, int data)
{
	if (node == NULL)
	{
		/* Element is not found */
		return NULL;
	}
	if (data > node->data)
	{
		/* Search in the right sub tree. */
		return Find(node->right, data);
	}
	else if (data < node->data)
	{
		/* Search in the left sub tree. */
		return Find(node->left, data);
	}
	else
	{
		/* Element Found */
		return node;
	}
}

void PrintInorder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
	PrintInorder(node->left);
	printf("%d ", node->data);
	PrintInorder(node->right);
}

void PrintPreorder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
	printf("%d ", node->data);
	PrintPreorder(node->left);
	PrintPreorder(node->right);
}

void PrintPostorder(treeNode *node)
{
	if (node == NULL)
	{
		return;
	}
	PrintPostorder(node->left);
	PrintPostorder(node->right);
	printf("%d ", node->data);
}

int counter (treeNode *p)
{
	if (p == NULL)
		return(0);
	else
	if (p->left == NULL && p->right == NULL)
		return(1);
	else
		return(1 + (counter(p->left) + counter(p->right)));
}

void in_order_sum (treeNode *p)
{
	if (!p)
	{
		return;
	}
	in_order_sum(p->left);
	sum = sum + p->data;
	in_order_sum(p->right);
}

treeNode * find_kth_element_iterative (treeNode *tree, int &k)
{
	if (tree == 0)
		return 0;

	treeNode *node = tree;
	int count = 0;
	int pos = k;


	while (node != 0) {
		count = 0;

		//count nodes on the left subtree  
		count=counter(node->left);

		//check if root is the median  
		if (pos == count + 1)
			return node;

		//check if median falls on left subtree  
		else if (count >= pos)
			node = node->left;

		//median falls on right subtree  
		else {
			pos -= (count + 1);
			node = node->right;
		}

	}
	return 0;
}
treeNode* medianTraverse (treeNode *root, int treeSize)
{
	while (treeSize)
	{
		if (root)
		{
			treeSize--;
			medianTraverse(root->left, treeSize);
				return root;
				medianTraverse(root->right, treeSize);

		}
	}
	return root;
}

int findHeight(treeNode *aNode)
{
	if (aNode == 0)
		return -1;

	int lefth = findHeight(aNode->left);
	int righth = findHeight(aNode->right);

	if (lefth > righth)
		return lefth + 1;
	else
		return righth + 1;
}
/* Print nodes at a given level */
void printGivenLevel(treeNode* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		printf("%d ", root->data);
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}
void printLevelOrder(treeNode* root)
{
	int h = findHeight(root);
	int i;
	for (i = 1; i <= h; i++)
	{

		printGivenLevel(root, i);
		printf("\n");
	}
}



int main()
{
	treeNode *root = NULL;
	int x;
	int ch, num, num1;
	treeNode * temp;
	treeNode *med;
	int m = 1;

	do {
		printf("\nSelect a choice from the menu below.");
		printf("\n1. Generate Binary Search Tree");
		printf("\n2. Print the BST in pre-order format");
		printf("\n3. Print the BST in in-order format");
		printf("\n4. Print the BST in post-order format");
		printf("\n5. Print the BST in breadth-first format");
		printf("\n6. Find a value in the BST");
		printf("\n7. Find the minimum value in the BST nodes");
		printf("\n8. Find the maximum value in the BST nodes");
		printf("\n9. Calculate the average value of the BST nodes");
		printf("\n10. Find the median value of the BST nodes");
		printf("\n11. Calculate the sum of the BST nodes");
		printf("\n12. Count the number of BST nodes");
		printf("\n13. Delete a value in the BST");
		printf("\n14. Exit Program");
		printf("\n");
		printf("\nEnter Choice: ");
		scanf("%d", &ch);
		switch (ch) {
		case 1: 
			FILE *ifp;
			
			ifp = fopen("AssignmentFourInput.txt", "r");

			if (ifp == NULL) {
				fprintf(stderr, "Can't open input file AssignmentFourInput.txt!\n");
				exit(1);
			}

			int val;

			while (!feof(ifp)) {
				fscanf(ifp, "%d", &val);

				root = Insert(root, val);
			}
			printf("\n");
			printf("\nTree in IN-ORDER : ");
			PrintInorder(root);
			printf("\n");
			break;

		case 2:
			PrintPreorder(root);
			break;

		case 3: 
			PrintInorder(root);
			break;

		case 4:
			PrintPostorder(root);
			break;
		case 5:
			printLevelOrder(root);
			break;
		case 6:
			printf("\nEnter the element to be Find in TREE: ");
			scanf("%d", &num);
			temp=Find(root, num);
			if (temp->data == num)
			{
				printf("Element Found\n");
			}
			else
			{
				printf("Element NOT Found\n");
			}
			break;
		case 7:
			temp = FindMin(root);
			printf("Minimum element is %d\n", temp->data);
			break;
		case 8:
			temp = FindMax(root);
			printf("Maximum element is %d\n", temp->data);
			break;
		case 9:
			in_order_sum(root);
			printf("Average element is %d\n", sum / counter(root));
			sum = 0;
			break;
		case 10:
			med = medianTraverse(root, findHeight(root));
			printf("Median Value is %d\n", med->data);
			break;
		case 11:
			in_order_sum(root);
			printf("\nThe sum of all the elements are:%d\n", sum);
			sum = 0;
			break;
		case 12:
			printf("Total Number of Nodes %d\n", counter(root));
			break;
		case 13:
			PrintInorder(root);
			printf("\n");
			printf("\nEnter the element to be Deleted: ");
			scanf("%d", &num);
			Delete(root, num);
			break;
		case 14:
			exit(0);
			break;

		default: exit(0);
		}
		//printf("%d", rootNode->data);
		printf("\n");
		printf("\nIf you want to return to the menu, press 1.");
		printf("\nChoice: ");
		scanf("%d", &num);
	} while (num == 1);
	
}