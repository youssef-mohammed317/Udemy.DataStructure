#include "PolynomialByLinkedList.h"

// --- Private Helper Methods ---

void PolynomialByLinkedList::ThrowIfFull() {
	try {

		PolynomialNode* newNode = new PolynomialNode(1, 1);
		delete newNode;
	}
	catch (exception& e)
	{
		throw runtime_error("the poly is full");
	}
}

// --- Constructors & Destructor ---

PolynomialByLinkedList::PolynomialByLinkedList() {
	length = 0;
	head = tail = nullptr;
}

PolynomialByLinkedList::PolynomialByLinkedList(const PolynomialByLinkedList& other) {
	this->length = 0;
	this->head = nullptr;
	this->tail = nullptr;
	PolynomialNode* curr = other.head;
	while (curr != nullptr) {

		PolynomialNode* newNode = new PolynomialNode(curr->GetCoeff(), curr->GetPower());


		if (head == nullptr)
		{
			head = tail = newNode;
		}
		else {
			this->tail->SetNext(newNode);
			this->tail = newNode;
		}

		this->length++;
		curr = curr->GetNext();
	}
}

PolynomialByLinkedList::~PolynomialByLinkedList() {
	Clear();
}

// --- Core Functionality ---

void PolynomialByLinkedList::Clear() {

	PolynomialNode* temp = head;
	while (head != nullptr)
	{
		temp = head;
		head = head->GetNext();
		delete temp;
	}
	head = tail = nullptr;
	length = 0;
}

void PolynomialByLinkedList::AddTerm(double coeff, int power) {

	ThrowIfFull();

	if (head == nullptr)
	{
		head = tail = new PolynomialNode(coeff, power);
		length++;
	}
	else if (power > head->GetPower())
	{
		head = new PolynomialNode(coeff, power, head);
		length++;
	}
	else if (power < tail->GetPower())
	{
		PolynomialNode* node = new PolynomialNode(coeff, power);
		tail->SetNext(node);
		tail = node;
		length++;
	}
	else if (head->GetPower() == power)
	{
		double newCoeff = head->GetCoeff() + coeff;
		if (newCoeff != 0)
		{
			head->SetCoeff(newCoeff);
		}
		else
		{
			PolynomialNode* temp = head;
			head = head->GetNext();
			delete temp;
			length--;

			if (head == nullptr)
				head = tail = nullptr;

		}
	}

	else if (tail->GetPower() == power)
	{
		double newCoeff = tail->GetCoeff() + coeff;
		if (newCoeff != 0)
		{
			tail->SetCoeff(newCoeff);
		}
		else
		{
			PolynomialNode* temp = head;
			while (temp->GetNext() != tail)
				temp = temp->GetNext();

			temp->SetNext(nullptr);
			delete tail;
			tail = temp;
			length--;
		}
	}
	else {
		PolynomialNode* curr = head->GetNext();
		PolynomialNode* prev = head;

		while (curr != nullptr)
		{
			if (curr->GetPower() == power)
			{
				double newCoeff = curr->GetCoeff() + coeff;
				if (newCoeff != 0)
				{
					curr->SetCoeff(newCoeff);
				}
				else {
					prev->SetNext(curr->GetNext());
					delete curr;
					length--;
				}
				return;
			}
			else if (prev->GetPower() > power && curr->GetPower() < power)
			{
				prev->SetNext(new PolynomialNode(coeff, power, curr));
				length++;
				return;
			}

			prev = curr;
			curr = curr->GetNext();
		}
	}

}

int PolynomialByLinkedList::GetTermCoeff(int power) {

	PolynomialNode* curr = head;

	while (curr != nullptr)
	{
		if (curr->GetPower() == power)
			return curr->GetCoeff();

		curr = curr->GetNext();
	}

	return 0;
}

double PolynomialByLinkedList::Calc(double val) {

	double total = 0;
	PolynomialNode* curr = head;

	while (curr != nullptr)
	{
		total += curr->Calc(val);

		curr = curr->GetNext();
	}
	return total;
}

void PolynomialByLinkedList::Display()
{
	cout << "P(x) = ";
	if (head == nullptr)return;


	cout << head->GetCoeff();
	if (head->GetPower() != 0)
		cout << "x^" << head->GetPower();



	PolynomialNode* curr = head->GetNext();
	while (curr != nullptr)
	{
		double coeff = curr->GetCoeff();
		if (coeff < 0)
		{
			cout << " - ";

			if (coeff != -1)
				cout << -coeff;
		}
		else
		{
			cout << " + ";
			if (coeff != 1)
				cout << coeff;
		}
		if (curr->GetPower() != 0)
		{
			cout << "x^" << curr->GetPower();
		}
		curr = curr->GetNext();
	}
}

void PolynomialByLinkedList::TestBehavior() {
	cout << "--- Testing PolynomialByLinkedList ---" << endl;

	try {
		// 1. Create First Polynomial (P1)
		PolynomialByLinkedList p1;
		p1.AddTerm(5, 2);  // 5x^2
		p1.AddTerm(3, 1);  // 3x^1
		p1.AddTerm(7, 0);  // 7
		p1.AddTerm(-2, 4); // -2x^4 (Tests inserting at head)
		p1.AddTerm(1, 3);  // 1x^3 (Tests middle insertion)

		cout << "\nPolynomial 1 (P1):" << endl;
		p1.Display();
		cout << endl;

		// 2. Test Evaluation (Calc)
		cout << "P1 evaluated at x = 2: " << p1.Calc(2) << " (Expected: -2(16) + 1(8) + 5(4) + 3(2) + 7 = 9)" << endl;

		// 3. Create Second Polynomial (P2)
		PolynomialByLinkedList p2;
		p2.AddTerm(2, 4);  // 2x^4  (Will cancel out P1's -2x^4)
		p2.AddTerm(-5, 2); // -5x^2 (Will cancel out P1's 5x^2)
		p2.AddTerm(10, 0); // 10

		cout << "\nPolynomial 2 (P2):" << endl;
		p2.Display();
		cout << endl;

		// 4. Test Operator+ (Addition)
		cout << "\nResult of P1 + P2:" << endl;
		PolynomialByLinkedList p3 = p1 + p2;
		p3.Display();
		// Expected: P(x) = 1x^3 + 3x^1 + 17
		cout << endl;

	}
	catch (const exception& e) {
		cout << "Caught Exception: " << e.what() << endl;
	}

	cout << "--- Test Complete ---" << endl;
}
// --- Operators ---

PolynomialByLinkedList PolynomialByLinkedList::operator+(const PolynomialByLinkedList& s) const {

	PolynomialByLinkedList sum = PolynomialByLinkedList();

	PolynomialNode* p = head;
	PolynomialNode* q = s.head;

	while (p != nullptr && q != nullptr)
	{
		if (p->GetPower() == q->GetPower())
		{
			double newCoeff = p->GetCoeff() + q->GetCoeff();
			if (newCoeff != 0)
				sum.AddTerm(newCoeff, p->GetPower());
			p = p->GetNext();
			q = q->GetNext();
		}
		else if (p->GetPower() > q->GetPower())
		{
			sum.AddTerm(p->GetCoeff(), p->GetPower());
			p = p->GetNext();
		}
		else
		{
			sum.AddTerm(q->GetCoeff(), q->GetPower());
			q = q->GetNext();

		}
	}
	while (p != nullptr)
	{
		sum.AddTerm(p->GetCoeff(), p->GetPower());
		p = p->GetNext();
	}
	while (q != nullptr)
	{
		sum.AddTerm(q->GetCoeff(), q->GetPower());
		q = q->GetNext();
	}



	return sum;
}