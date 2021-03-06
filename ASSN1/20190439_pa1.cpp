#include <iostream>
#include <fstream>
#include "utils.h"

using namespace std;


/* 
    [Task 1] Choose the TIGHT bound of the following arrayMax function
    
    *arrayMax*
        Input
        - int n: the length of the input array (n >=1)
        - int* A: an array storing n >= 1 integers
        Output
        - int: the maximum element in A
        int arrayMax(int n, int* A) {
            int currMax = A[0];
            for (int i=1; i < n; i++)
                if (currMax < A[i])
                    currMAx = A[i];
            return currMax;
        }

    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
    int answer = 2;  // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the TIGHT bound of the following prefixAverages function

    *prefixAverages*
        Input
        - int n: the length of the input array (n >=1)
        - double* X: an array storing n >= 1 real numbers
        Output
        - double*: An n-element array A of real numbers such
                  that A[i] is the average of elements X[0], … , X[i]
        double* prefixAverages(int n, double* X) {
            double *A = new double[n];
            double sum;
            for (int i = 0; i < n; i++) {
                sum = 0;
                for (int j = 0; j <= i; j++)
                    sum = sum + X[j];
                A[i] = sum / (i+1);
            }
            return A;
        }

    Choices
        1: O( log(n) )
        2: O( log^2(n) )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_2(ofstream &fout) {
    int answer = 4;  // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function which can append an integer or insert “0” into the list. 
        An user can specify the position where 0 will be inserted.
        If the index is out of range of the given list, print “error”

    Input:
        Sequence of commands, which is one of the following
        - (‘append’, integer): append {integer} at the tail of list
        - (‘insert_at’, index): insert “0” at the index

    Output: 
        - Values in the list, in string separated with spacebar
        - “error” if the index is out of range
*/
void task_3(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
	
	struct NODE {
		NODE* next;
		int data;
	};
	
	struct HEAD {
		NODE* head;
		NODE* tail;
		int length;
	};

	HEAD list = { NULL, NULL, 0};
    for (int i=0; i<instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("append") == 0) {
			if (list.head == NULL)
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = NULL;
				list.head = node;
				list.tail = node;
				list.length++;
			}
			else
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = NULL;
				list.tail->next = node;
				list.tail = node;
				list.length++;
			}


		}
		else if (command.compare("insert_at") == 0) {
			int number = instr_seq->instructions[i].value - 1;
			if (number + 1 > list.length)
			{
				answer = "error";
				break;
			}
			else
			{
				if (number == -1)
				{
					NODE* node = new NODE;
					node->data = 0;
					node->next = list.head;
					list.head = node;
					list.tail = node;
					list.length++;
				}
				else
				{
					if (list.length == number + 1)
					{
						NODE* Current = list.head;
						for (int i = 0; i < number; i++)
						{
							Current = Current->next;
						}

						NODE* node = new NODE;
						node->data = 0;
						node->next = NULL;
						Current->next = node;
						list.tail = node;
						list.length++;
					}
					else
					{
						NODE* Current = list.head;
						for (int i = 0; i < number; i++)
						{
							Current = Current->next;
						}

						NODE* node = new NODE;
						node->data = 0;
						node->next = Current->next;
						Current->next = node;
						list.length++;
					}
				}
			}
        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
	
	if (answer != "error")
	{
		for (NODE* Current = list.head; Current != NULL; Current = Current->next)
		{
			char size[100];
			_itoa_s(Current->data, size, 10);
			answer = answer + size;
			if (Current->next == NULL)
			{
				break;
			}
			answer = answer + " ";
		}
	}
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    fout << "[Task 3]" << endl;
    fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function which shows the value in the stack from the top after a sequence of “push” operation

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’, integer): push {integer} into the current stack

    Output:
        - Values in the stack from the top to the bottom, in string separated with spacebar
*/
void task_4(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;
    
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
	struct NODE {
		NODE* next;
		int data;
	};

	struct HEAD {
		NODE* head;
		int length;
	};
	HEAD stack = { NULL, 0 };

    for (int i=0; i<instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("push") == 0) {
            /* TODO: Implement */
			if (stack.head == NULL)
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = NULL;
				stack.head = node;
				stack.length++;
			}
			else
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = stack.head;
				stack.head = node;
				stack.length++;
			}



        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
	for (NODE* Current = stack.head; Current != NULL; Current = Current->next)
	{
		char size[100];
		_itoa_s(Current->data, size, 10);
		answer = answer + size;
		if (Current->next == NULL)
		{
			break;
		}
		answer = answer + " ";
	}
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 4]" << endl;
    fout << answer << endl;
}

/*
    [Task 5] Stack

    Description:
        Implement a function which shows the value in the stack from the top after the sequence of “push” or “pop” operations. 
        If the stack is empty then print “empty”.
        If “pop” operation from the empty stack then print “error”

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’, integer): push integer into the current stack
        - (‘pop’, NULL): pop the top value of the current stack
    
    Output: 
        - Values in the stack from the top to the bottom, in string separated with spacebar
        - “empty” if the resulting stack is empty
        - “error” if the pop operation is executed on empty stack
*/
void task_5(ofstream &fout, InstructionSequence* instr_seq) {
    string answer; 

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
	struct NODE {
		NODE* next;
		int data;
	};

	struct HEAD {
		NODE* head;
		int length;
	};
	HEAD stack = { NULL, 0 };

    for (int i=0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("push") == 0) {
            /* TODO: Implement */
			if (stack.head == NULL)
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = NULL;
				stack.head = node;
				stack.length++;
			}
			else
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = stack.head;
				stack.head = node;
				stack.length++;
			}

        } else if (command.compare("pop") == 0) {
            /* TODO: Implement */
			if (stack.length <= 0)
			{
				answer = "error";
				break;
			}
			else if(stack.length > 1)
			{
				stack.head = stack.head->next;
				stack.length--;
			}
			else
			{
				stack.head = NULL;
				stack.length--;
			}

        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

	if (answer != "error")
	{
		if (stack.length == 0)
		{
			answer = "empty";

		}
		else
		{
			for (NODE* Current = stack.head; Current != NULL; Current = Current->next)
			{
				char size[100];
				_itoa_s(Current->data, size, 10);
				answer = answer + size;
				if (Current->next == NULL)
				{
					break;
				}
				answer = answer + " ";
			}
		}
	}
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 5]" << endl;
    fout << answer << endl;
    
}

/*
    [Task 6] Queue

    Description: 
        Implement a function which shows the value of a queue after the  sequence of arbitrary queue operation. 
        If the queue after the operations is empty, print “empty”. 
        If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue 

    Output
        - Values in the queue from the head to the tail, in string separated with spacebar 
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on empty queue
*/
void task_6(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;
    
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
	struct NODE {
		NODE* next;
		int data;
	};

	struct HEAD {
		NODE* front;
		NODE* rear;
		int length;
	};
	HEAD queue = { NULL, 0 };

    for (int i=0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("enqueue") == 0) {
            /* TODO: Implement */
			if (queue.front == NULL)
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = NULL;
				queue.front = node;
				queue.rear = node;
				queue.length++;
			}
			else
			{
				NODE* node = new NODE;
				node->data = instr_seq->instructions[i].value;
				node->next = NULL;
				queue.rear->next = node;
				queue.rear = node;
				queue.length++;
			}

        } else if (command.compare("dequeue") == 0) {
            /* TODO: Implement */
			if (queue.length <= 0)
			{
				answer = "error";
				break;
			}
			else if (queue.length > 1)
			{
				queue.front = queue.front->next;
				queue.length--;
			}
			else
			{
				queue.front = NULL;
				queue.rear = NULL;
				queue.length--;
			}

        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
	if (answer != "error")
	{
		if (queue.length == 0)
		{
			answer = "empty";
		}
		else
		{
			for (NODE* Current = queue.front; Current != NULL; Current = Current->next)
			{
				char size[100];
				_itoa_s(Current->data, size, 10);
				answer = answer + size;
				if (Current->next == NULL)
				{
					break;
				}
				answer = answer + " ";
			}
		}
	}
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 6]" << endl;
    fout << answer << endl;
}


int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence* instr_seq;

    // Open file
    ofstream fout;
    fout.open(filename, fstream::app);
    if (!fout.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Choosing task number. Default is running ALL tasks (0)
    if (argc >= 2)
        task_num = atoi(argv[1]);
    if (argc >= 3) {
        try {
            instr_seq = ParseInstructions(argv[2]);
        }
        catch (const char* e) {
            cerr << e << endl;
            return -1;
        }
    }

    // Running the task(s)
    switch (task_num) {
        case 1:
            task_1(fout);
            break;
        case 2:
            task_2(fout);
            break;
        case 3:
            task_3(fout, instr_seq);
            break;
        case 4:
            task_4(fout, instr_seq);
            break;
        case 5:
            task_5(fout, instr_seq);
            break;
        case 6:
            task_6(fout, instr_seq);
            break;
        case 0:
            task_1(fout);
            task_2(fout);

            InstructionSequence* instr_seq_3;
            instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq_3);
            
            InstructionSequence* instr_seq_4;
            instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq_4);
            
            InstructionSequence* instr_seq_5;
            instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq_5);
            
            InstructionSequence* instr_seq_6;
            instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq_6);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}