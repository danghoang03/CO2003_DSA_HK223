//#include "common.h"

#ifndef _common_h_
#include "common.h"
#define _common_h_
#endif

//////////////////////////////////////////////////////////////
//
//			Some common functions
//
//////////////////////////////////////////////////////////////
int convertToInt(digitList *head){
    int num = 0;
    int pow = 1;
    while(head != NULL){
        num += head->digit * pow;
        pow *= 10;
        head = head->nextDigit;
    }
    return num;
}


digitList *digitize(char str[80])
{
	digitList*	L = 0;
	digitList*	node;

	int i;

	for(i = 0; i< strlen(str); i++){
		if(str[i] < '0' || str[i] > '9')	break;

		node = new digitList(str[i] - '0', L);
		L = node;
	}
	char digit = str[i];

	if(digit == '!'){
        int num = convertToInt(L);
        if(num == 0)
            return new digitList(1,NULL);
        Integer I1 = Integer(1, L);
        for(int i = num - 1; i > 0; i--){
            I1 = I1 * Integer(i);
        }
        return I1.digits;
	}
    else if(digit == '^'){
        if(convertToInt(L) == 0)
            return NULL;
        digitList* L2 = 0;
        for(i = i + 1; i < strlen(str); i++){
            node = new digitList(str[i] - '0', L2);
            L2 = node;
        }
        int exponent = convertToInt(L2);
        if(exponent == 0)
            return new digitList(1, NULL);
        Integer I1 = Integer(1, L);
        Integer I2 = Integer(1, L);
        for(int i = 1; i < exponent; i++){
            I1 = I1 * I2;
        }
        return I1.digits;
	}

	return L;

}

digitList *trimDigitList(digitList* L)
{
    if(L == NULL) return NULL;

	digitList *lastPositionNonZero = NULL; //Xac dinh vi tri phan tu khac 0 cuoi cung trong danh sach
	digitList *curr = L;

	while(curr != NULL){
        if(curr->digit != 0){
            lastPositionNonZero = curr;
        }
        curr = curr->getNextDigit();
	}

	//Neu tat ca phan tu trong danh sach deu la 0
	if(lastPositionNonZero == NULL) return NULL;
	// Xoa cac chu so 0 con lai o cuoi danh sach
	curr = lastPositionNonZero->nextDigit;
	lastPositionNonZero->nextDigit = NULL;
	while(curr != NULL){
        digitList *pDel = curr;
        curr = curr->getNextDigit();
        delete pDel;
	}
	return L;
}

digitList *subDigitLists(int b, digitList* L1, digitList* L2)
{
    /* Vi trong phan hien thuc qua tai toan tu, ta luon dam bao rang ham subDigitLists se thuc hien phep tru giua so lon L1
      voi so nho hon la L2. Do L1 > L2 nen se khong xay ra truong hop L1 == NULL khi L2 van con phan tu.*/
    if(L1 == NULL && L2 == NULL){
        return NULL;
    }
    if(L2 == NULL){
        int hieu = L1->getDigit() - b;
        if(hieu < 0)
            return new digitList(hieu + 10, subDigitLists(1, L1->getNextDigit(), NULL));
        else
            return new digitList(hieu, subDigitLists(0, L1->getNextDigit(), NULL));
    }
    else if(L1 != NULL && L2 != NULL){
        int hieu = L1->getDigit() - L2->getDigit() - b;
        if(hieu < 0)
            return new digitList(hieu + 10, subDigitLists(1, L1->getNextDigit(), L2->getNextDigit()));
        else
            return new digitList(hieu, subDigitLists(0, L1->getNextDigit(), L2->getNextDigit()));
    }
    else
        return NULL;
}


Integer computeValue(int operatorNum)
{
	Integer		L1, L2;

	L1 = operandArr[0];

	//L1.trimDigit();

	for(int i = 0; i<operatorNum; i++)
	{
		L2 = operandArr[i+1];
        //L2.trimDigit();
		switch(operatorArr[i])
		{
		case '+':
			L1 = L1 + L2;
			break;
        case '-':
            L1 = L1 - L2;
            break;
        case '*':
            L1 = L1 * L2;
            break;
		}
	}

	return L1;
}

digitList *pushZeroToList(digitList *head, int L)
{
    int n = L - head->length();
    digitList *lastDigit = head;

    //Tim phan tu cuoi cung trong danh sach
    while(lastDigit->getNextDigit() != NULL){
        lastDigit = lastDigit->getNextDigit();
    }

    //Them so 0 vao cuoi danh sach
    for(int i = 0; i < n; i++){
        digitList *newDigit = new digitList(0, NULL);
        lastDigit -> nextDigit = newDigit;
        lastDigit = newDigit;
    }

    return head;
}

///////////////////////////////////////////////////////////////////////////
//
//		Some methods of Integer class
//
////////////////////////////////////////////////////////////////////
Integer Integer::operator +(Integer L)
{
	if(sign == L.sign){
        return Integer(sign, addDigitLists(0, digits, L.digits)).trimDigit();
	}
    else if(sign == -1 && L.sign == 1){
        if(compareDigitLists(digits, L.digits) == 1)
            return Integer(sign, subDigitLists(0, digits, L.digits)).trimDigit();
        else if(compareDigitLists(digits, L.digits) == -1)
            return Integer(L.sign, subDigitLists(0, L.digits, digits)).trimDigit();
        else
            return Integer();
    }
    else if(sign == 1 && L.sign == -1){
        if(compareDigitLists(digits, L.digits) == 1)
            return Integer(sign, subDigitLists(0, digits, L.digits)).trimDigit();
        else if(compareDigitLists(digits, L.digits) == -1)
            return Integer(L.sign, subDigitLists(0, L.digits, digits)).trimDigit();
        else
            return Integer();
    }
}


Integer Integer::operator -(Integer L)
{
	if(sign == 1 && L.sign == 1){
        if(compareDigitLists(digits, L.digits) == 1)
            return Integer(sign, subDigitLists(0, digits, L.digits)).trimDigit();
        else if(compareDigitLists(digits, L.digits) == -1)
            return Integer(-1, subDigitLists(0, L.digits, digits)).trimDigit();
        else
            return Integer();
	}
	else if(sign == -1 && L.sign == 1)
        return Integer(sign, addDigitLists(0, digits, L.digits));
    else if(sign == 1 && L.sign == -1)
        return Integer(sign, addDigitLists(0, digits, L.digits));
    else{
        if(compareDigitLists(digits, L.digits) == 1)
            return Integer(sign, subDigitLists(0, digits, L.digits)).trimDigit();
        else if(compareDigitLists(digits, L.digits) == -1)
            return Integer(1, subDigitLists(0, L.digits, digits)).trimDigit();
        else
            return Integer();
    }
}

Integer Integer::leftDigits(int n)
{
    if(digits == NULL || n <= 0) return Integer();
    digitList *leftDigitsList = digits->leftDigits(n);
    return Integer(1, leftDigitsList);
}

Integer Integer::rightDigits(int n)
{
    if(digits == NULL || n <= 0) return Integer();
    digitList *rightDigitsList = digits->rightDigits(n);
    return Integer(1, rightDigitsList);
}

Integer	Integer::shift(int n)
{
    if(n == 0) return Integer(sign, digits);

    digitList *shiftedList = digits;

    //Them so 0 vao dau danh sach de thuc hien phep nhan voi 10^n
    for(int i = 0; i < n; i++){
        digitList* newDigit = new digitList(0, NULL);
        newDigit->nextDigit = shiftedList;
        shiftedList = newDigit;
    }

    return Integer(sign, shiftedList);
}


Integer Integer::operator *(Integer Y)
{
	int L = max(digits->length(), Y.digits->length());

    //So sanh chieu dai X va Y. Them cac so 0 vao sau so co do dai nho hon
	if(Y.digits->length() < L){
        Y.digits = pushZeroToList(Y.digits, L);
	}
	else if(digits->length() < L){
        digits = pushZeroToList(digits, L);
	}
    //Nhan hai so co 1 chu so
	if(digits->length() == 1){
        int product = digits->getDigit() * Y.digits->getDigit();
        if(product == 0)
           return Integer();
        else
            return Integer(1, digitize(product));
	}

	//Nhan hai so co nhieu chu so
	else{
        Integer result;
        int n = L/2;
        Integer xLeft = leftDigits(n);
        Integer xRight = rightDigits(L - n);
        Integer yLeft = Y.leftDigits(n);
        Integer yRight = Y.rightDigits(L - n);
        result = (xLeft * yLeft) + ((xRight * yLeft) + (xLeft * yRight)).shift(n) + (xRight * yRight).shift(2*n);
        if(sign == Y.sign)
            result.sign = 1;
        else
            result.sign = -1;
    return result;
	}
}
