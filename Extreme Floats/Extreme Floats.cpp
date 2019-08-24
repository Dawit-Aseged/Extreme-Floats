#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
#pragma warning(disable : 4996)
struct node
{
	node* behind;
	node* next;
	char digit;
};

int lengthOfNodeFromBack(node*);
int lengthOfNode(node*);

void create(node*& head, node*& tail)
{
	head = NULL;
	tail = NULL;
}

void insertNode(node*& head, node*& tail, node*& p, node*& prev)
{
	if (prev == NULL)
	{
		// This is insertion at the head.
		if (head == NULL)
		{
			/*
			This is insertion at the head and
			the linked list is empty.
			*/
			head = p;
			tail = p;
			p->next = NULL;
			p->behind = NULL;
		}
		else
		{
			/*
			This is insertion at the head of a
			non-empty linked list.
			*/
			p->behind = NULL;
			p->next = head;
			p->next->behind = p; //Makes sure the next element points to the element to be inserted.
			head = p;
		}

	}
	else if (prev->next == NULL)
	{
		/*
		This is insertion at the tail.
		*/
		p->next = NULL;
		p->behind = tail;
		p->behind->next = p; // Makes sure the previous element points to the element to be inserted.
		tail = p;
	}
	else
	{
		/*
		This is insertion at any middle part of the linked list.
		*/
		p->next = prev->next;
		p->behind = prev;
		p->next->behind = p;
		prev->next = p;
	}
}


void deleteNode(node*& head, node*& tail, node*& p)
{
	if (lengthOfNode(head) == 1)
	{
		head = NULL;
		tail = NULL;
		delete p;
		return;
	}
	if (p->behind == NULL)
	{
		/*
		This is deletion at the head.
		*/
		head = head->next;
		head->behind = NULL;
	}

	else if (p->next != NULL)
	{
		/*
		This is deletion at middle part of the linked list.
		*/
		p->behind->next = p->next;
		p->next->behind = p->behind;
	}
	else
	{
		/*
		This is deletion at the tail.
		*/

		p->behind->next = NULL;
		tail = p->behind;

	}

	delete p;
}

void deleteNodeAtTail(node*& tail, node*& p)
{
	if (lengthOfNodeFromBack(tail) == 1)
	{
		tail = NULL;
		delete p;
	}
	else
	{
		node* head = NULL;
		deleteNode(head, tail, p);
	}
}
void insertNodeAtHead(node*& head, node*& tail, node*& p)
{
	node* prev = NULL;
	insertNode(head, tail, p, prev);
}

void insertNodeAtTail(node*& head, node*& tail, node*& p)
{
	node* prev = tail;
	insertNode(head, tail, p, prev);
}
void displayNumber(node* head)
{
	while (head != NULL)
	{
		cout << head->digit;
		head = head->next;
	}
}

void displayNumberReverse(node* tail)
{

	while (tail != NULL)
	{
		cout << tail->digit;
		tail = tail->behind;
	}
}
void displayMenu()
{
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------- Extreme Calculator --------------------------------------\n";
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << endl << endl;
}
int precision()
{
	cout << "Please enter a precision:- ";
	int pre;
	cin >> pre;
	return pre;
}

char toChar(int x)
{
	//Changes the input of integer to a character;
	if (x >= 0 && x <= 9)
		return (x + 48);
	else
		return 0;
}

int toInt(char c)
{
	//Changes the input of character to integer;
	return c - 48;
}


int lengthOfNode(node* head)
{
	int cnt = 0;
	while (head != NULL)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}

int lengthOfNodeFromBack(node* tail)
{
	int cnt = 0;
	while (tail != NULL)
	{
		cnt++;
		tail = tail->behind;
	}
	return cnt;
}


int trim(node*& tail)
{
	node* p = tail;
	int cnt = 0;
	if (lengthOfNodeFromBack(tail) == 1 && tail->digit == '0')
		return 0;
	while (tail->digit == '0')
	{
		/*
		The loop traverses through the linked list from the back.
		when it finds the character '0', it deletes it. This search
		goes on until the last element is a non-zero element.
		*/
		tail = tail->behind;
		tail->next = NULL;
		delete p;
		p = tail;
		cnt++;
	}
	//It counts the number of digits it removed from the rear.
	return cnt;
}

void trimHeadAndTail(node*& head, node*& tail, int& digits, int& exponent, int& sign)
{
	node* p = NULL;
	while (head->digit == '0')
	{
		p = head;
		deleteNode(head, tail, p);
		exponent--;
		digits--;
	}
	while (tail->digit == '0')
	{
		p = tail;
		deleteNode(head, tail, p);
		digits--;
	}
	if (head == NULL)
		sign = 0;
}

void getNumberExponent(node*& head, node*& tail, int& exponent, int& digits, int& sign)
{
	cout << "Enter a number" << endl;
	char ch;
	bool isDotPressed = false;
	bool isZero = true;
	bool isSigned = false;

	exponent = digits = 0;

	ch = '0'; //It must have a valid character to enter the loop below.

	while ((ch <= '9' && ch >= '0') || ch == '.' || ch == '-')
	{

		/*
		The only valid characters are the digits and the decimal point.
		*/
		ch = getche(); //Gets an individual character from the user.

		if (ch == '-')
		{
			/*
			If the negative sign is pressed twice then the loop terminates.
			*/
			if (isSigned)
				break;
			else
			{
				//If it was pressed for the first time, it changes the sign to a negative 1.
				isSigned = true;
				sign = -1;
			}
			//This digit must not be added to the linked list, so the loop restarts.
			continue;
		}

		if (ch == '\r')
		{
			/*
			If enter is pressed and the only digits there are zero then the exponent, digits and sign must be zero.
			*/
			if (isZero)
			{
				isSigned = true;
				exponent = 0;
				digits = 0;
				sign = 0;
			}

			continue;
		}
		if (ch == '.')
		{
			/*
			If the decimal point is pressed more than once, it will automatically
			exit the loop.
			*/
			if (isDotPressed)
				break;
			else
				isDotPressed = true;
			continue;
		}



		if (ch != '0')
			isZero = false;

		if (!isDotPressed && isZero)
		{
			/*
			This ignores all redundant zeros before a non-zero digit before the decimal.
			*/
			continue;
		}

		digits++;

		if (isDotPressed && isZero)
		{
			/*
			If the decimal point is pressed and there are only zeros,
			it decreases the exponent but does not add it to the linked list.
			*/
			exponent--;
			continue;
		}
		node* p = new node;
		p->digit = ch;
		if (p != NULL)
		{
			if (!isDotPressed)
				exponent++;
			insertNodeAtTail(head, tail, p);
		}
	}
	if (!isSigned)
	{
		//When the number is finished being inputted and it is neither negative nor zero, it must be positive.
		sign = 1;
	}
	if (tail == NULL)
	{
		node* p = new node;
		p->digit = '0';
		insertNodeAtTail(head, tail, p);
	}
	digits -= trim(tail);
}

void displayNumberExponent(node* head, int exponent, int sign)
{
	bool dotIsSet = false;
	if (sign == -1)
		cout << '-';
	node* p = new node;

	while (head != NULL)
	{
		if (exponent > 0)
		{
			while (exponent > 0)
			{
				/*
				This displays all the digits before the decimal point.
				*/
				if (head != NULL)
				{
					p = head;
					head = head->next;
				}
				else
					p->digit = '0';
				cout << p->digit;

				exponent--;
			}
			if (head != NULL)
			{
				cout << '.';
				dotIsSet = true;
			}

			else
				break;
		}
		else if (exponent < 0)
		{
			if (!dotIsSet)
				cout << "0.";
			dotIsSet = true;
			while (exponent < 0)
			{
				/*
				This displays all the zeros before the first non-zero element.
				*/
				cout << '0';
				exponent++;
			}
		}
		else
		{
			if (!dotIsSet)
			{
				cout << "0.";
				dotIsSet = true;
			}
		}
		/*
		This displays the rest of the digits.
		*/
		cout << head->digit;
		head = head->next;

	}
}

void addExponent(node* tail1, node* tail2, int exponent1, int exponent2, int digit1, int digit2, node*& sumHead, node*& sumTail, int& sumExponent)
{
	node* p = new node;
	int carry = 0;

	//The exponent of the sum is the largest of the 2 operands
	if (exponent1 > exponent2)
		sumExponent = exponent1;
	else
		sumExponent = exponent2;

	int afterDecimal1, afterDecimal2;


	if (exponent1 <= 0)
		afterDecimal1 = digit1;
	else
		afterDecimal1 = digit1 - exponent1;

	if (exponent2 <= 0)
		afterDecimal2 = digit2;
	else
		afterDecimal2 = digit2 - exponent2;


	while (afterDecimal1 > afterDecimal2)
	{
		/*
		Matches the digits that have different length
		E.g. 3.21
				 +
			 0.0101
			 -------
				 01
		This occurs for which ever number has the largest number of digits after the decimal point.
		Hence, there are two loops.
		*/

		/*
		If the number is very small and the last non-zero digits is transfered to the sum linked list,
		the linked list that holds the numbers becomes empty. If that number is empty, but if the number of digits
		is greater than the second number, then zero is simply added to the sum linked list.
		*/

		if (tail1 == NULL)
			p->digit = '0';

		else
		{
			p->digit = tail1->digit;
			tail1 = tail1->behind;
		}
		insertNodeAtHead(sumHead, sumTail, p);
		p = new node;
		afterDecimal1--;

	}
	while (afterDecimal2 > afterDecimal1)
	{

		if (tail2 == NULL)
			p->digit = '0';
		else
		{
			p->digit = tail2->digit;
			tail2 = tail2->behind;
		}
		insertNodeAtHead(sumHead, sumTail, p);
		p = new node;
		afterDecimal2--;
	}


	/*
	The below loop continues until both numbers have evaluated to their most significant
	digit. However, there might be a carry by the sum of the most significant digits, therefore
	we add an extra digit and then we terminate the sum.
	*/
	int cnt = 0;
	while ((tail1 != NULL || tail2 != NULL) || carry)
	{
		int val1, val2;

		/*
		There are four possibilities when it comes to adding digits.
				|   Tail 1  |   Tail 2  |
		--------|-----------|-----------|--
			1   |    NULL   |  NOT NULL |
		--------|-----------|-----------|--
			2   |  NOT NULL |    NULL   |
		--------|-----------|-----------|--
			3   |  NOT NULL |  NOT NULL |
		--------|-----------|-----------|--
			4   |    NULL   |    NULL   |
		--------|-----------|-----------|--

		*/

		bool tail1Pushed = false;
		bool tail2Pushed = false;


		while ((lengthOfNodeFromBack(tail1) < exponent1) && (lengthOfNodeFromBack(tail2) < exponent2) && (lengthOfNodeFromBack(tail1) > 0) && (lengthOfNodeFromBack(tail2) > 0))
		{
			/*
			Simply add zero if the exponents of is greater than the number of digits.
			*/
			cnt++;
			p->digit = '0';
			insertNodeAtHead(sumHead, sumTail, p);
			exponent1--;
			exponent2--;
			p = new node;

		}
		if ((lengthOfNodeFromBack(tail1) < exponent1) && (lengthOfNodeFromBack(tail2) >= exponent2))
		{
			exponent1--;
			val1 = 0;
			tail1Pushed = true;
		}

		else if ((lengthOfNodeFromBack(tail1) >= exponent1) && (lengthOfNodeFromBack(tail2) < exponent2))
		{
			exponent2--;
			val2 = 0;
			tail2Pushed = true;
		}


		if (tail1 == NULL && tail2 != NULL)
		{
			val1 = 0;
			val2 = toInt(tail2->digit);
		}
		else if (tail1 != NULL && tail2 == NULL)
		{
			val1 = toInt(tail1->digit);
			val2 = 0;
		}
		else if (tail1 != NULL && tail2 != NULL)
		{
			val1 = toInt(tail1->digit);
			val2 = toInt(tail2->digit);
		}
		else
		{
			val1 = val2 = 0;
			if (carry)
				sumExponent++;
		}
		if (tail1Pushed)
			val1 = 0;
		if (tail2Pushed)
			val2 = 0;

		int sum = carry + val1 + val2;
		if (sum <= 9)
		{
			/*
			If the sum of two digits is less than nine,
			including the carry of the digit before, then the
			carry becomes zero and the digit is put in the sum
			linked list.
			*/
			carry = 0;
			p->digit = toChar(sum);
			insertNodeAtHead(sumHead, sumTail, p);

			if (tail1 != NULL)
				if (!tail1Pushed)
				{
					tail1 = tail1->behind;
					exponent1--;
				}
			if (tail2 != NULL)
				if (!tail2Pushed)
				{
					tail2 = tail2->behind;
					exponent2--;
				}

			p = new node;
		}
		else
		{
			/*
			Since the largest possible outcome of the sum of two single digit numbers
			including the carry is 19, we know that the carry is 1. The remainder is added
			to the sum linked list and the carry is taken to the next digit.
			*/
			carry = 1;
			p->digit = toChar(sum % 10);
			insertNodeAtHead(sumHead, sumTail, p);
			if (tail1 != NULL)
				if (!tail1Pushed)
				{
					tail1 = tail1->behind;
					exponent1--;
				}

			if (tail2 != NULL)
				if (!tail2Pushed)
				{

					tail2 = tail2->behind;
					exponent2--;
				}
			p = new node;

		}

	}
}
int isGreater(node* head1, node* head2, int digits1, int digits2, int exponent1, int exponent2)
{
	/*
	If one exponent is greater than the other, then obviously that number is greater than the
	other.
	*/
	if (exponent1 > exponent2)
		return 1;
	else if (exponent2 > exponent1)
		return -1;

	while (head1 != NULL || head2 != NULL)
	{
		/*
		If they have equal exponents then it compares the digits starting from the most significant figure
		downwards. If there is no digit left but there still is an exponent, then the digit '0' is inserted
		to ensure a comparison is made.
		*/
		int val1, val2;

		if (head1 == NULL)
			val1 = '0';
		else
			val1 = head1->digit;

		if (head2 == NULL)
			val2 = '0';
		else
			val2 = head2->digit;

		if (toInt(val1) > toInt(val2))
			return 1;
		else if (toInt(head1->digit) < toInt(head2->digit))
			return -1;
		head1 = head1->next;
		head2 = head2->next;
	}

	/*
	If the numbers have been compared and without returning both heads have become null, the numbers must have been equal.
	*/
	return 0;

}

void subtractBigMinusSmall(node* tail1, node* tail2, int exponent1, int exponent2, int afterDecimal1, int afterDecimal2, node*& returnHead, node*& returnTail, int& returnExponent)
{

	node* p = new node;
	node* p2 = new node;
	returnExponent = exponent1;
	int carry = 0;
	while (afterDecimal1 > afterDecimal2)
	{
		/*
		If the number of excess decimal digits is greater on the first number, the excess digits
		are simply passed to the result linked list.
		*/
		if (tail1 == NULL)
			p->digit = '0';
		else
		{
			p->digit = tail1->digit;
			tail1 = tail1->behind;
		}
		insertNodeAtHead(returnHead, returnTail, p);
		p = new node;
		afterDecimal1--;

	}
	while (afterDecimal2 > afterDecimal1)
	{
		/*
		If the the number of excess decimal digits is greater on the second number, those digits have to
		be subtracted from newly generated digits (having value '0') and getting carry from the number before them.
		*/
		if (tail2 == NULL)
		{

			p = new node;
			p->digit = '0';
		}

		else
			p->digit = tail2->digit;

		p2 = tail1;
		/*
		For the least significant digit the value it will be subtracted from is 10 (0 value + 10 carry).
		For the rest it value to be subtracted from is 9 (0 value + 9 carry).
		*/
		p->digit = toChar(10 - carry - toInt(p->digit));
		insertNodeAtHead(returnHead, returnTail, p);
		if (tail2 != NULL)
		{
			tail2 = tail2->behind;
		}


		carry = 1;
		p = new node;
		if (tail2 != NULL)
			p->digit = tail2->digit;
		else
			p->digit = '0';
		afterDecimal2--;

		if (afterDecimal1 == afterDecimal2)
		{

			do
			{

				if (p2->digit == '0')
				{
					p2->digit = '9';
					carry = 1;
				}
				else
				{
					p2->digit = toChar(toInt(p2->digit) - 1);
					carry = 0;
				}
				p2 = p2->behind;

			} while (carry);
		}


		p = new node;

	}
	carry = 0;

	while (tail1 != NULL)
	{
		/*
		This loop traverses through the rest of the elements.
		*/
		int val1, val2;
		p = new node;
		/*
		If there is no carry then, val1 is just tail of the subtractee.
		Otherwise, it is that tail of the subtractee plus 10.
		*/
		val1 = toInt((tail1->digit) + (10 * carry));


		if (tail2 == NULL) //If there are no more digits to be subtracted, the value to be subtracted will be zero.
			val2 = 0;
		else
			val2 = toInt(tail2->digit);
		if (val1 >= val2)
		{
			/*
			If the subtractee digit is greater or equal than the subtractor, then it takes the difference
			and puts it in the result linked list.
			*/
			p->digit = toChar(val1 - val2);
			tail1 = tail1->behind;
			if (tail2 != NULL)
				tail2 = tail2->behind;
			insertNodeAtHead(returnHead, returnTail, p);
			carry = 0;

		}
		else
		{
			/*
				If the subtractor digit is greater than subtractee, it takes a carry from previous digits and gives the carry element value 1.
			*/
			p = tail1;
			while (p->behind->digit == '0')
			{

				if (p->behind->digit == '0')
					p->behind->digit = '9';
				else
					p->behind->digit = toChar(toInt(p->behind->digit) - 1);
				p = p->behind;
			}
			p->behind->digit = toChar(toInt(p->behind->digit) - 1);
			carry = 1;
		}
	}

}
void subtract(node* subtracteeHead, node* subtractorHead, node* subtracteeTail, node* subtractorTail, int subtracteeExponent, int subtractorExponent, int subtracteeDigits, int subtractorDigits, int subtracteeSign, int subtractorSign, node*& differenceHead, node*& differenceTail, int& differenceExponent, int& differenceSign)
{
	node* p = new node;
	int carry = 0;
	int afterDecimalSubtractor, afterDecimalSubtractee;
	if (subtractorExponent <= 0)
		afterDecimalSubtractor = subtractorDigits;
	else
		afterDecimalSubtractor = subtractorDigits - subtractorExponent;

	if (subtracteeExponent <= 0)
		afterDecimalSubtractee = subtracteeDigits;
	else
		afterDecimalSubtractee = subtracteeDigits - subtracteeExponent;
	if (subtracteeSign != subtractorSign)
	{
		if (subtractorSign = -1)
		{
			differenceSign = 1;
			addExponent(subtracteeTail, subtractorTail, subtracteeExponent, subtractorExponent, subtracteeDigits, subtractorDigits, differenceHead, differenceTail, differenceExponent);
		}
		else
		{
			differenceSign = -1;
			addExponent(subtracteeTail, subtractorTail, subtracteeExponent, subtractorExponent, subtracteeDigits, subtractorDigits, differenceHead, differenceTail, differenceExponent);
		}
		return;
	}
	else
	{
		if (subtracteeSign == 1)
		{

			int value = isGreater(subtracteeHead, subtractorHead, subtracteeDigits, subtractorDigits, subtracteeExponent, subtractorExponent);

			if (value == 1)
			{
				differenceSign = 1;
				subtractBigMinusSmall(subtracteeTail, subtractorTail, subtracteeExponent, subtractorExponent, afterDecimalSubtractee, afterDecimalSubtractor, differenceHead, differenceTail, differenceExponent);
			}
			else if (value == -1)
			{
				differenceSign = -1;
				subtractBigMinusSmall(subtractorTail, subtracteeTail, subtractorExponent, subtracteeExponent, afterDecimalSubtractor, afterDecimalSubtractee, differenceHead, differenceTail, differenceExponent);

			}
			else
			{
				differenceSign = 0;
				differenceHead = NULL;
				differenceTail = NULL;
				differenceExponent = 0;
			}
		}
		else if (subtracteeSign == -1)
		{
			int value = isGreater(subtracteeHead, subtractorHead, subtracteeDigits, subtractorDigits, subtracteeExponent, subtractorExponent);
			if (value == 1)
			{
				differenceSign = -1;
				subtractBigMinusSmall(subtracteeTail, subtractorTail, subtracteeExponent, subtractorExponent, afterDecimalSubtractee, afterDecimalSubtractor, differenceHead, differenceTail, differenceExponent);
			}
			else if (value == -1)
			{
				differenceSign = 1;
				subtractBigMinusSmall(subtractorTail, subtracteeTail, subtractorExponent, subtracteeExponent, afterDecimalSubtractor, afterDecimalSubtractee, differenceHead, differenceTail, differenceExponent);

			}
			else
			{
				differenceSign = 0;
				differenceHead = NULL;
				differenceTail = NULL;
				differenceExponent = 0;
			}
		}
		else
		{
			differenceSign = 0;
			differenceHead = NULL;
			differenceTail = NULL;
			differenceExponent = 0;
		}
	}
	int differenceDigits = lengthOfNode(differenceHead);
	//trimHeadAndTail(differenceHead,differenceTail,differenceDigits,differenceExponent,differenceSign);
	/*
	Just add the subtraction possibilities and use the add function. Also make sure the add function works negative numbers as well.
	Adjust the sign or else the add and subtract function will call themselves until the stack has overflown.
	*/
	return;


}

void decrementByOneWithoutExponent(node*& head, node*& tail, int& digits, int& exponents, int& sign)
{
	if (tail != NULL)
	{
		node* p = new node;
		p = tail;
		if (p->digit == '0')
		{
			trimHeadAndTail(head, tail, digits, exponents, sign);

		}
		p->digit = toChar(toInt(p->digit) - 1);
	}
}

void destroyLinkedList(node*& head, node*& tail)
{
	
	while (head != NULL)
	{
		node* p = head;
		deleteNode(head, tail, p);
	}
}



void copyLinkedList(node*& head1, node*& tail1, node* head2)
{
	create(head1, tail1);
	node* p = new node;
	p->digit = head2->digit;
	while (p != NULL)
	{
		insertNodeAtTail(head1, tail1, p);
		p = new node;
		head2 = head2->next;
		if (head2 != NULL)
			p->digit = head2->digit;
		else
			p = NULL;
	}
}
void multiply(node* head1, node* tail1, node* head2, node* tail2, int exponent1, int exponent2, int digit1, int digit2, int sign1, int sign2, node*& productHead, node*& productTail, int& productExponent, int& productSign)
{

	int num1afterDecimal, num2afterDecimal, productAfterDecimal;
	/*
	This gets the number of digits after the decimal of the first number.
	*/
	if (exponent1 <= 0)
		num1afterDecimal = digit1;
	else
		num1afterDecimal = digit1 - exponent1;
	/*
	This gets the number of digits after the decimal of the second number.
	*/
	if (exponent2 <= 0)
		num2afterDecimal = digit2;
	else
		num2afterDecimal = digit2 - exponent2;

	productAfterDecimal = num1afterDecimal + num2afterDecimal;
	node* pseudoSumHead;
	node* pseudoSumTail;
	int pseudoSumExponent = 0;
	int pseudoSumDigits = 0;
	create(pseudoSumHead, pseudoSumTail);
	
	node* productCloneHead;
	node* productCloneTail;
	int productCloneExponent = 0;
	int productCloneDigits = 0;
	create(productCloneHead, productCloneTail);

	node* p = new node;
	p->digit = '0';
	insertNodeAtHead(productCloneHead, productCloneTail, p);
	p = NULL;

	int counter = 0;

	while (tail2 != NULL)
	{
		node* num1 = new node;
		node* num2 = new node;
		node* p = new node;
		
		int carry = 0;
		num1 = tail1;
		num2->digit = tail2->digit;

		for(int i = 0; i < counter; i++)
		{
			node* x = new node;
			x->digit = '0';
			insertNodeAtHead(pseudoSumHead, pseudoSumTail, x);
			pseudoSumDigits++;
			pseudoSumExponent++;
		}
		while (num1 != NULL)
		{
			int product = toInt(num1->digit) * toInt(num2->digit) + carry;
			cout << endl;
			cout << "Num 1 digit: " << num1->digit << endl;
			cout << "Num 2 digit: " << num2->digit << endl;
			cout << "Product is : " << product << endl;
			cout << "Carry is : " << carry << endl;
		
			
			int result = product % 10;
			if (num1->behind == NULL)
			{
				while (product)
				{
					cout << endl << endl << endl << endl << "INTERNAL PRODUCT: " << product << endl << endl;
					p->digit = toChar(result);
					insertNodeAtHead(pseudoSumHead, pseudoSumTail, p);
					pseudoSumDigits++;
					pseudoSumExponent++;
					p = new node;
					product /= 10;
					result = product;
				}
				num1 = num1->behind;
				
				continue;
				
			}
			cout << " Result is : " << result << endl;
			p->digit = toChar(result);
			insertNodeAtHead(pseudoSumHead, pseudoSumTail, p);
			pseudoSumDigits++;
			pseudoSumExponent++;
			carry = product / 10;
			num1 = num1->behind;
			p = new node;

			
		}
		/*
		In order to add psedo sum to the product head
		1. The product linked list is emptied.
		2. The product clone and psedo sum are added and then put into product linked list.
		3. The product clone linked list is emptied. 
		4. The product is copied to product clone.
		5. The pseudo sum linked list is emptied.
		*/

		/*1*/destroyLinkedList(productHead, productTail);
		
		/*2*/addExponent(productCloneTail, pseudoSumTail, productCloneExponent, pseudoSumExponent, productCloneDigits, pseudoSumDigits, productHead, productTail, productExponent);
		
		/*3*/destroyLinkedList(productCloneHead, productCloneTail);
		/*4*/copyLinkedList(productCloneHead, productCloneTail, productHead);
		
		/*5*/destroyLinkedList(pseudoSumHead, pseudoSumTail);
		destroyLinkedList(productHead, productTail);
		
		addExponent(productCloneTail, pseudoSumTail, productCloneExponent, pseudoSumExponent, productCloneDigits, pseudoSumDigits, productHead, productTail, productExponent);
		destroyLinkedList(productCloneHead, productCloneTail);
		
		copyLinkedList(productCloneHead, productCloneTail, productHead);
		destroyLinkedList(pseudoSumHead, pseudoSumTail);
		productCloneExponent = productExponent;
		
		
		//(lengthOfNode(productHead) > productExponent) ? productCloneDigits = lengthOfNode(productHead) : productCloneDigits = productExponent;
		if (lengthOfNode(productHead) > productExponent)
			productCloneDigits = lengthOfNode(productHead);
		else
			productCloneDigits = productExponent;
		pseudoSumDigits = pseudoSumExponent = 0;

		cout << "Product Clone digits: " << productCloneDigits << endl;;
		tail2 = tail2->behind;
		counter++;
		

		//p = 




	}

	return;
	
	/*
	/*
		The following paragraph of code creates a linked list with only one element.
		The value of that element is 1.
	

	node* valueOneHead;
	node* valueOneTail;
	int valueOneDigits = 1;
	int valueOneExponent = 1;
	int valueOneSign = 1;
	create(valueOneHead, valueOneTail);
	node* p = new node;
	p->digit = '1';
	insertNodeAtHead(valueOneHead, valueOneTail, p);
	//p = NULL;

	node* addSecondaryHead;
	node* addSecondaryTail;
	int addSecondaryExponent = exponent1;
	int addSecondaryDigits = digit1;
	create(addSecondaryHead, addSecondaryTail);

	node* subtractSecondaryHead;
	node* subtractSecondaryTail;
	int subtractSecondaryExponent = exponent2;
	int subtractSecondaryDigits = digit2;
	int subtractSecondarySign = 1;
	create(subtractSecondaryHead, subtractSecondaryTail);

	copyLinkedList(addSecondaryHead, addSecondaryTail, head1);

	if (sign1 == sign2)
		productSign = 1;
	else
		productSign = -1;

	int digitsSubtract = 0;

	if (digit2 > exponent2)
		digitsSubtract = digit2;
	else
		digitsSubtract = exponent2;

	int digSubSave = digitsSubtract;

	cout << endl << "PLANE DIGITS: "; displayNumber(head2);
	cout << endl << " Old Exponent: " << exponent2 << endl;
	cout << endl << "Number with exponent: "; displayNumberExponent(head2, exponent2, sign2);
	cout << endl << "Number with max expnent: "; displayNumberExponent(head2, digitsSubtract, sign2); cout << " New Exponent: " << digitsSubtract;
	while (toInt(head2->digit) != 0)
	{
		addExponent(addSecondaryTail, tail1, addSecondaryExponent, exponent1, addSecondaryDigits, digit1, productHead, productTail, productExponent);
		copyLinkedList(addSecondaryHead, addSecondaryTail, productHead);

		subtract(head2, valueOneHead, tail2, valueOneTail, exponent2, valueOneExponent, digit2, valueOneDigits, sign2, valueOneSign, subtractSecondaryHead, subtractSecondaryTail, subtractSecondaryExponent, subtractSecondarySign);
		cout << endl << "--------------------------------------" << endl;
		displayNumberExponent(head2, digitsSubtract, sign2);
		cout << endl << "--------------------------------------" << endl;

		copyLinkedList(head2, tail2, subtractSecondaryHead);
		create(subtractSecondaryHead, subtractSecondaryTail);
		//cout<<endl<<"Subtract: "<<head2->digit<<endl;
	}
	productExponent -= digSubSave;
	*/
}

void divide(node* head1, node* tail1, node* head2, node* tail2, int exponent1, int exponent2, int digit1, int digit2, int sign1, int sign2, node*& answerHead, node*& answerTail, int& answerExponent, int& answerSign, int precision)
{
	/*
	If the two numbers to be divided have the same sign then it is positive.
	If they have different signs, it is negative. 
	If one of the signs is zero, then the sign of the answer is zero
	*/
	destroyLinkedList(answerHead, answerTail);
	if (sign1 == sign2)
		answerSign = 1;
	else
		answerSign = -1;
	if (sign1 == 0 || sign2 == 0)
		answerSign = 0;

	sign1 = sign2 = 1; // This is to make sure that operation that involve the difference of the original numbers is only done in absolute value.
	bool isFullyDivided = false;
	bool isExponentFixed = false;
	/*
	The following linked list has only one element and it has the value 1.
	This is the one to be incremented on the counter.
	*/
	node* oneHead;
	node* oneTail;
	create(oneHead,oneTail);
	int oneExpnent = 1;
	int oneDigit = 1;
	int oneSign = 1;
	node* p = new node;
	p->digit = '1';
	insertNodeAtHead(oneHead, oneTail, p);

	/*
	This will ultimately be the quotient of subsequent divides.
	*/
	node* counterHead;
	node* counterTail;
	create(counterHead, counterTail);
	int counterExponent = 1;
	int counterDigit = 1;
	int counterSign = 1;
	p = new node;
	p->digit = '1';
	insertNodeAtHead(counterHead, counterTail, p);

	/*
	Temporary linked list that holds different data depending upon the situation;
	*/
	node* productCheckerHead;
	node* productCheckerTail;
	create(productCheckerHead, productCheckerTail);
	int productCheckerExponent = 0;
	int productCheckerDigits = 0;
	int productCheckerSign = 0;
	

	int intermediateExponent = 0;
	int precisionCopy = precision;
	while (precisionCopy > 0 && !isFullyDivided)
	{
		cout << endl << "Head: ";
		displayNumber(head1);
		cout << endl;
		
		/*
		Multiplies the denomeinator 'n' times.
		*/
		multiply(counterHead, counterTail, head2, tail2, counterExponent, exponent2, counterDigit, digit2, counterSign, sign2, productCheckerHead, productCheckerTail, productCheckerExponent, productCheckerSign);
		
		/*
		Set the value of the product's digits.
		*/
		int len = lengthOfNode(productCheckerHead);
		if (len > productCheckerExponent)
			productCheckerDigits = len;
		else
			productCheckerDigits = productCheckerExponent;

		int comparisionValue = isGreater(productCheckerHead, head1, productCheckerDigits, digit1, productCheckerExponent, exponent1);
		if (comparisionValue >= 0)
		{
			
			/*
			This occurs if the product of the counter and the denominator is greater than that numerator.
			The following code simply means:
				
					counter--;
			*/
			if (comparisionValue != 0)
			{
				destroyLinkedList(productCheckerHead, productCheckerTail);
				subtract(counterHead, oneHead, counterTail, oneTail, counterExponent, oneExpnent, counterDigit, oneDigit, counterSign, oneSign, productCheckerHead, productCheckerTail, productCheckerExponent, productCheckerSign);
				destroyLinkedList(counterHead, counterTail);
				copyLinkedList(counterHead, counterTail, productCheckerHead);
			}
			
			//int counterExponentCopy = counterExponent
			while (counterHead != NULL || counterExponent!=0)
			{
				
				/*
				Copies all the reqired digits to the answer linked list.
				*/
				node* p = new node;
				if (counterHead != NULL)
				{
					p->digit = counterHead->digit;
					counterHead = counterHead->next;
					
				}
				else
					p->digit = '0'; // If expnent is greater than the number of digits then the value 0 is added to the answer.
				counterExponent--;
				insertNodeAtTail(answerHead, answerTail, p);
				//cout << endl << "=> ";
				//displayNumber(answerHead);
				//cout << endl;
				
			}

			if (!isExponentFixed) // This occurs once to set the expnent of the answer.
			{
				isExponentFixed;
				answerExponent = productCheckerExponent;
			}
			if (comparisionValue == 0)
			{
				isFullyDivided = true;  // If the number is fully divided.
				return;
			}
			int len = lengthOfNode(productCheckerHead);
			if (len > productCheckerExponent)
				productCheckerDigits = len;
			else
				productCheckerDigits = productCheckerExponent;

			destroyLinkedList(productCheckerHead, productCheckerTail);
			counterExponent++;
			multiply(counterHead, counterTail, head2, tail2, counterExponent, exponent1, counterDigit, digit2, counterSign, sign2, productCheckerHead, productCheckerTail, productCheckerExponent, productCheckerSign); // Holds the product of counter and denominator
			destroyLinkedList(counterHead, counterTail); //Clears space 
			len = lengthOfNode(productCheckerHead); // Gets approperiate productCheckerDigits
			if (len > productCheckerExponent)
				productCheckerDigits = len;
			else
				productCheckerDigits = productCheckerExponent;
			cout << "PE->" << counterExponent;
			cout << endl << "Counter 1: "; displayNumberExponent(counterHead, counterExponent, sign1); 
			cout << endl;
			cout << endl << "Product :"; displayNumberExponent(productCheckerHead, productCheckerExponent, 1);
			cout << endl;

			subtract(head1, productCheckerHead, tail1, productCheckerTail,exponent1, productCheckerExponent, digit1, productCheckerDigits, sign1, productCheckerSign, counterHead, counterTail, counterExponent, counterSign); // Subtracts product from tail1
			destroyLinkedList(head1, tail1);
			copyLinkedList(head1, tail1, counterHead); // Replaces the numerator for further evaluation
			exponent1 = counterExponent;

			cout << "Changed : "; displayNumberExponent(head1, exponent1, sign1);

			len = lengthOfNode(counterHead); 
			if (len > counterExponent)	//Gets approperiate digits for the numerator
				digit1 = len;
			else
				digit1 = counterExponent;
			
			len = lengthOfNode(answerHead);
			int answerDigit;
			if (len > answerExponent)
				answerDigit = len;
			else
				answerDigit = answerExponent;

			precisionCopy = precision - answerDigit;
			
		}
		else
		{
			/*
			The following code is simply:
				
					counterTail++;
			*/
			
			destroyLinkedList(productCheckerHead, productCheckerTail);
			addExponent(counterTail,oneTail,counterExponent, oneExpnent,counterDigit,oneDigit,productCheckerHead,productCheckerTail,productCheckerExponent); //In this cas product checker holds the counterTail++;
			destroyLinkedList(counterHead, counterTail);
			copyLinkedList(counterHead, counterTail, productCheckerHead);
			
			int len = lengthOfNode(counterHead);
			if (len > counterExponent)
				counterDigit = len;
			else
				counterDigit = counterExponent;
			counterExponent = productCheckerExponent; //Sets approperiate exponent to counter.
			destroyLinkedList(productCheckerHead, productCheckerTail);
		}
	}
}

int main()
{

	node* head1, * tail1, * head2, * tail2;
	node* resultHead, * resultTail;
	int digitsAfterDecimal1, digitsAfterDecimal2;
	int digits1, digits2;
	int exponent1, exponent2, resultExponent;
	int sign1, sign2, resultSign;
	create(head1, tail1);
	create(head2, tail2);
	create(resultHead, resultTail);
	displayMenu();
	getNumberExponent(head1, tail1, exponent1, digits1, sign1);
	cout << endl;
	cout<<"Number 1 Digits: "<<digits1<<" Exponents 1 : "<<exponent1;

	cout << endl;
	getNumberExponent(head2, tail2, exponent2, digits2, sign2);

	cout << endl;

	//  cout<<"NUM 2: ";

	addExponent(tail1, tail2, exponent1, exponent2, digits1, digits2, resultHead, resultTail, resultExponent);
	resultSign = 1;
	 // cout<<"Number 2 Digits: "<<digits2<<" Exponents 2 : "<<exponent2;
	  //cout<<"Exponent 1 Before Subtract: "<<exponent1<<endl;
	  //cout<<"Exponent 2 Before Subtract: "<<exponent2<<endl;
	  subtract(head1, head2, tail1, tail2, exponent1, exponent2, digits1, digits2, sign1, sign2, resultHead, resultTail, resultExponent, resultSign);
	//multiply(head1, tail1, head2, tail2, exponent1, exponent2, digits1, digits2, sign1, sign2, resultHead, resultTail, resultExponent, resultSign);

	//divide(head1, tail1, head2, tail2, exponent1, exponent2, digits1, digits2, sign1, sign2, resultHead, resultTail, resultExponent, resultSign,15);

	  cout<<"The answer is ";
	displayNumberExponent(resultHead, resultExponent, resultSign);
	cout << endl;
	return 0;

}
