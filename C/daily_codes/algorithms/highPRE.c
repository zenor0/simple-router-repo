#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define PRECISION 100
#define Max(A,B) ((A > B) ? A : B)
void ReverseString(char *input);
void GetNumber(char *dest);
int CharNumCompare(char const *inputA, char const *inputB);
//void SimpleMultiply(char const *input, int mulNum, int *result);
//make sure result array is long enough
void Addition(char const *inputA, char const *inputB, char result[]);	//result max(inputA, inputB) + 1	/ precision + 1
bool Minus(char const *inputA, char const *inputB, char result[]);	//result max(inputA, inputB)	/ precision
bool Multiply(char const *inputA, char const *inputB, char result[]);	//result inputA + inputB
int main(void)
{
	//initialize & input
	char inputA[PRECISION];
	char inputB[PRECISION];
	memset(inputA, '0', sizeof(inputA));
	memset(inputB, '0', sizeof(inputB));
	scanf("%s", inputA);
	scanf("%s", inputB);


	int resultLength = Max(strlen(inputA), strlen(inputB)) + 2;
	char result[resultLength];
	memset(result, '0', sizeof(result));
	Multiply(inputA, inputB, result);
	//output
	bool isBegin = false;

	printf("%s", result);

	return 0;
}

void ReverseString(char *input)
{
	int len = strlen(input);
	int limit = len / 2;
	char temp;
	for (int i = 0; i < limit; i++)
	{
		//swap 2 char
		temp = input[i];
		input[i] = input[len - 1 - i];
		input[len - 1 - i] = temp;
	}
	input[len] = '0';
}
void Addition(char const *inputA, char const *inputB, char result[])
{
	int resultLength = Max(strlen(inputA), strlen(inputB)) + 1;

	char numA[resultLength + 1];
	char numB[resultLength + 1];
	memset(numA, '0', sizeof(numA));
	memset(numB, '0', sizeof(numB));
	numA[resultLength] = '\0';
	numB[resultLength] = '\0';

	strncpy(numA, inputA, strlen(inputA));
	strncpy(numB, inputB, strlen(inputB));
	//	int tempCount = 0;
	//	while (inputA[tempCount] != '\0')
	//	{
	//		numA[tempCount] = inputA[tempCount];
	//	}
	//	tempCount = 0;
	//	while (inputB[tempCount] != '\0')
	//	{
	//		numB[tempCount] = inputB[tempCount];
	//	}


	ReverseString(numA);
	ReverseString(numB);

	//add
	int resultRev[resultLength];
	memset(resultRev, 0, sizeof(resultRev));
	int carryDigit = 0;
	for (int i = 0; i < resultLength; i++)
	{
		resultRev[i] = (numA[i] - '0') + (numB[i] - '0') + carryDigit;
		carryDigit = resultRev[i] / 10;
		resultRev[i] %= 10;
	}

	//store into char result
	bool isBegin = false;
	int count = 0;
	for (int i = 0; i < resultLength; i++)
	{
		if (resultRev[resultLength - 1 - i] != 0 || isBegin == true)
		{
			isBegin = true;
			result[count] = resultRev[resultLength - 1 - i] + '0';
			count++;
		}
	}
	result[count] = '\0';

}


bool Minus(char const *inputA, char const *inputB, char result[])
{
	//check if inputA > inputB
	//use a flag to store the sign of result
	if (CharNumCompare(inputA, inputB) < 0)
	{
		Minus(inputB, inputA, result);
		return false;
	}

	int resultLength = Max(strlen(inputA), strlen(inputB));
	char numA[resultLength];
	char numB[resultLength];
	memset(numA, '0', sizeof(numA));
	memset(numB, '0', sizeof(numB));

	strcpy(numA, inputA);
	strcpy(numB, inputB);

	ReverseString(numA);
	ReverseString(numB);

	int resultRev[resultLength];
	memset(resultRev, 0, sizeof(resultRev));

	int carryDigit = 0;
	for (int i = 0; i < resultLength; i++)
	{
		resultRev[i] = (numA[i] - '0') - (numB[i] - '0') + carryDigit;
		if (resultRev[i] < 0)
		{
			resultRev[i] += 10;
			carryDigit = -1;
		}
		else
		{
			carryDigit = 0;
		}
		resultRev[i] %= 10;
	}

	bool isBegin = false;
	int count = 0;
	for (int i = 0; i < resultLength; i++)
	{
		if (resultRev[resultLength - 1 - i] != 0 || isBegin == true)
		{
			isBegin = true;
			result[count] = resultRev[resultLength - 1 - i] + '0';
			count++;
		}
	}
	result[count] = '\0';

	return true;
}
//void SimpleMultiply(char const *input, int mulNum, int *result)
//{
//	char inputNum[PRECISION];
//	memset(inputNum, '0', sizeof(inputNum));
//	strcpy(inputNum, input);
//	ReverseString(inputNum);
//	int limit = strlen(input) + 2;
//	int carryDigit = 0;
//	for (int i = 0; i < limit; i++)
//	{
//		result[i] = mulNum * (inputNum[i] - '0') + carryDigit;
//		carryDigit = result[i] / 10;
//		result[i] %= 10;
//	}
//}

bool Multiply(char const *inputA, char const *inputB, char result[])
{
	//un-optimized version
	//swap inputA and inputB can save unnecessary operations
	bool signA = true;
	bool signB = true;
	if (inputA[0] == '-')
	{
		signA = false;
		inputA++;
	}
	if (inputB[0] == '-')
	{
		signB = false;
		inputB++;
	}

	int ALength = strlen(inputA);
	int BLength = strlen(inputB);
	int resultLength = ALength + BLength + 1;	//+1 intends to put \0 digit
	int mulNumLength = BLength;	//equals times of addition

	int cacheNum[ALength + 1];	//save temporary result
	int addCarryDigit = 0;
	int mulCarryDigit = 0;

	//make a copy of inputA then reverse it for next calculation
	char inputACopy[ALength + 1];	//+1 to match the cache size.
	memset(inputACopy, '0', sizeof(inputACopy));
	strcpy(inputACopy, inputA);
	ReverseString(inputACopy);

	int cacheLimit = ALength + 1;

	int resultRev[resultLength];
	memset(resultRev, 0, sizeof(resultRev));
	for (int i = 0; i < mulNumLength; i++)
	{
		for (int k = 0; k < cacheLimit; k++)
		{
			//multiply a digit of inputB and the whole num of inputA
			//use k to control inputA digit
			//use i to control inputB digit
			cacheNum[k] = (inputB[BLength - 1 - i] - '0') * (inputACopy[k] - '0') + mulCarryDigit;
			mulCarryDigit = cacheNum[k] / 10;
			cacheNum[k] %= 10;
		}

		//add to result
		for (int j = 0; j < cacheLimit; j++)
		{
			resultRev[i + j] = cacheNum[j] + resultRev[i + j] + addCarryDigit;
			addCarryDigit = resultRev[i + j] / 10;
			resultRev[i + j] %= 10;
		}
	}

	//save result into result array as char
	bool isBegin = false;
	int count = 0;
	for (int i = 0; i < resultLength; i++)
	{
		if (resultRev[resultLength - 1 - i] != 0 || isBegin == true)
		{
			isBegin = true;
			result[count] = resultRev[resultLength - 1 - i] + '0';
			count++;
		}
	}
	result[count] = '\0';

	return !(signA ^ signB);
}
int CharNumCompare(char const *inputA, char const *inputB)
{
	int lengthDiff = strlen(inputA) - strlen(inputB);
	if (lengthDiff > 0)	//A > B
	{
		return 1;
	}
	else if (lengthDiff == 0)
	{
		return strcmp(inputA, inputB);
	}
	else if (lengthDiff < 0)
	{
		return -1;
	}

}


void Factorial_High(int N, char *result)
{
	char tempNum[5];
	sprintf(result, "1");
	for (int i = 2; i <= N; i++)
	{
		sprintf(tempNum, "%d", i);
		Multiply(result, tempNum, result);
	}
}

void QuickPower_High(char const *base, int index, char *result)
{
	char baseCopy[PRECISION];
	sprintf(result, "1");
	strcpy(baseCopy, base);
	
	//	while (index > 0)
	//	{
	//		if (index % 2 == 1)
	//		{
	//			Multiply(result, baseCopy, result);
	//		}
	//		index /= 2;
	//		Multiply(baseCopy, baseCopy, baseCopy);
	//	}
	
	//bit operation
	while (index > 0)
	{
		if (index & 1)
		{
			Multiply(result, baseCopy, result);
		}
		index >>= 1;
		Multiply(baseCopy, baseCopy, baseCopy);
	}
}
