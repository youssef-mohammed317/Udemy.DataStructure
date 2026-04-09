#include "SparseMatrixByLinkedList.h"

// --- Private Helper Methods ---

void SparseMatrixByLinkedList::ThrowIfFull() {

	if (length == rows * cols)
		throw runtime_error("the matrix is full");
}

void SparseMatrixByLinkedList::ThrowIfIndexOutOfRange(int r, int c) {

	if (r > rows || c > cols || r < 1 || c < 1)
		throw invalid_argument("index is out of range");
}

// --- Constructor & Destructor ---

SparseMatrixByLinkedList::SparseMatrixByLinkedList(int rows, int cols) {
	if (rows < 1 || cols < 1)
		throw invalid_argument("size must be postive");
	this->rows = rows;
	this->cols = cols;
	this->length = 0;
	head = tail = nullptr;
}

// --- Copy Constructor ---
SparseMatrixByLinkedList::SparseMatrixByLinkedList(const SparseMatrixByLinkedList& other) {
	// 1. Copy the basic dimensions
	this->rows = other.rows;
	this->cols = other.cols;
	this->length = 0;
	this->head = nullptr;
	this->tail = nullptr;

	// 2. Walk through the 'other' matrix and duplicate every node
	SparseNode* curr = other.head;
	while (curr != nullptr) {
		// Create a BRAND NEW node in memory
		SparseNode* newNode = new SparseNode(curr->GetRaw(), curr->GetCol(), curr->GetData());

		// Because 'other' is already perfectly sorted, we can just append to the tail!
		if (this->head == nullptr) {
			this->head = this->tail = newNode;
		}
		else {
			this->tail->SetNext(newNode);
			this->tail = newNode;
		}

		this->length++;
		curr = curr->GetNext();
	}
}

SparseMatrixByLinkedList::~SparseMatrixByLinkedList() {
	Clear();
}

// --- Core Functionality ---

void SparseMatrixByLinkedList::Clear() {
	SparseNode* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->GetNext();
		delete temp;
	}
	head = tail = nullptr;
	length = 0;
}

int SparseMatrixByLinkedList::GetRows() {
	return rows;
}

int SparseMatrixByLinkedList::GetCols() {
	return cols;
}

int SparseMatrixByLinkedList::GetLength() {
	return length;
}

void SparseMatrixByLinkedList::Set(int row, int col, int data) {
	ThrowIfFull();
	ThrowIfIndexOutOfRange(row, col);


	SparseNode* node = new SparseNode(row, col, data);

	if (head == nullptr) // empty
	{
		head = tail = node;
	}
	else if (row < head->GetRaw() || (row == head->GetRaw() && col < head->GetCol()))
	{
		node->SetNext(head);
		head = node;
	}
	else if (row > tail->GetRaw() || (row == tail->GetRaw() && col > tail->GetCol()))
	{
		tail->SetNext(node);
		tail = node;
	}
	else {
		SparseNode* curr = head;
		SparseNode* prev = nullptr;

		while (curr != nullptr && (curr->GetRaw() < row || (curr->GetRaw() == row && curr->GetCol() < col)))
		{
			prev = curr;
			curr = curr->GetNext();
		}

		if (curr != nullptr && curr->GetRaw() == row && curr->GetCol() == col)
		{
			curr->SetData(data);
			delete node;
			return;
		}

		node->SetNext(curr);
		if (prev != nullptr)
			prev->SetNext(node);

	}
	length++;
}

int SparseMatrixByLinkedList::Get(int row, int col) {
	ThrowIfIndexOutOfRange(row, col);

	SparseNode* temp = head;

	while (temp != nullptr)
	{
		if (temp->GetCol() == col && temp->GetRaw() == row)
			return temp->GetData();

		temp = temp->GetNext();
	}
	return 0;
}
void SparseMatrixByLinkedList::Display() {
	SparseNode* curr = head;

	for (int r = 1; r <= rows; ++r) {
		cout << "{";

		for (int c = 1; c <= cols; ++c) {
			if (curr != nullptr && curr->GetRaw() == r && curr->GetCol() == c) {
				cout << curr->GetData();
				curr = curr->GetNext();
			}
			else {
				cout << "0";
			}

			if (c < cols) {
				cout << ", ";
			}
		}

		cout << "}\n";
	}
}
void SparseMatrixByLinkedList::TestBehavior() {
	cout << "--- Testing SparseMatrixByLinkedList ---" << endl;

	try {
		// 1. Create a 4x4 Sparse Matrix
		SparseMatrixByLinkedList matrix(4, 4);
		cout << "\nCreated 4x4 Matrix 1 (M1)." << endl;

		// 2. Set some values
		matrix.Set(1, 1, 5);
		matrix.Set(2, 3, 8);
		matrix.Set(4, 4, 2);
		matrix.Set(3, 1, 9); // Test out-of-order insertion

		// 3. Test Updating an existing value
		matrix.Set(2, 3, 99);
		cout << "Matrix 1 State:" << endl;
		matrix.Display();

		// 4. Test Get()
		cout << "\nTesting Get() method:" << endl;
		cout << "Value at (1,1): " << matrix.Get(1, 1) << " (Expected: 5)" << endl;
		cout << "Value at (2,3): " << matrix.Get(2, 3) << " (Expected: 99)" << endl;
		cout << "Value at (2,2): " << matrix.Get(2, 2) << " (Expected: 0)" << endl;

		// 5. Test Operator+ (Addition)
		cout << "\n--- Testing Operator+ ---" << endl;
		SparseMatrixByLinkedList m2(4, 4);
		m2.Set(1, 1, 10);  // Intersects with M1's (1,1). Expected sum: 15
		m2.Set(2, 3, -99); // Intersects with M1's (2,3). Expected sum: 0 (Should disappear)
		m2.Set(3, 3, 7);   // Brand new coordinate

		cout << "Matrix 2 (M2) State:" << endl;
		m2.Display();

		cout << "\nResult of M1 + M2:" << endl;
		SparseMatrixByLinkedList m3 = matrix + m2;
		m3.Display();

		// 6. Test Exception Handling (Out of Bounds)
		cout << "\nTesting Exception Handling..." << endl;
		matrix.Set(5, 5, 10); // Should throw

	}
	catch (const exception& e) {
		cout << "Caught Exception: " << e.what() << endl;
	}

	cout << "--- Test Complete ---" << endl;
}
// --- Operators ---

SparseMatrixByLinkedList SparseMatrixByLinkedList::operator+(SparseMatrixByLinkedList& s) {

	if (s.cols != cols || s.rows != rows)
		throw logic_error("cant add two diffrant sizes of matrix");

	SparseNode* p = head;
	SparseNode* q = s.head;
	SparseMatrixByLinkedList sum = SparseMatrixByLinkedList(rows, cols);

	while (p != nullptr && q != nullptr)
	{
		if (p->GetRaw() == q->GetRaw())
		{
			if (p->GetCol() == q->GetCol())
			{
				int data = p->GetData() + q->GetData();
				if (data != 0)
					sum.Set(p->GetRaw(), p->GetCol(), data);
				p = p->GetNext();
				q = q->GetNext();
			}
			else if (p->GetCol() < q->GetCol())
			{
				sum.Set(p->GetRaw(), p->GetCol(), p->GetData());
				p = p->GetNext();
			}
			else {

				sum.Set(q->GetRaw(), q->GetCol(), q->GetData());
				q = q->GetNext();
			}
		}
		else if (p->GetRaw() < q->GetRaw())
		{
			sum.Set(p->GetRaw(), p->GetCol(), p->GetData());
			p = p->GetNext();
		}
		else {

			sum.Set(q->GetRaw(), q->GetCol(), q->GetData());
			q = q->GetNext();
		}

	}

	while (q != nullptr)
	{
		sum.Set(q->GetRaw(), q->GetCol(), q->GetData());
		q = q->GetNext();
	}
	while (p != nullptr)
	{
		sum.Set(p->GetRaw(), p->GetCol(), p->GetData());
		p = p->GetNext();
	}

	return sum;
}