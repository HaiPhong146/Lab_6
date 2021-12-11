#include <iostream>
#include <vector>
#include <algorithm>
#define FOR(i,l,r) for(int i=l; i<r; i++)
#define FOD(i,l,r) for(int i=r-1; i>=l; i--)
using namespace std;

void Input(int*& a, int& pages, int& frames, int choice)
{
	if (choice == 2)
	{
		cout << "Nhap so trang: ";
		cin >> pages;
		a = new int[pages];
		cout << "Nhap gia tri tham chieu cua tung trang\n";
		FOR(i, 0, pages)
		{
			cout << "Nhap a[" << i << "]= ";
			cin >> a[i];
		}
		cout << "Nhap so luong khung trang: ";
		cin >> frames;
	}
	else
	{
		pages = 11;
		a = new int[pages];
		int b[] = { 2, 0, 5, 2, 1, 7, 4, 3, 0, 0, 7 };
		FOR(i, 0, 11)
		{
			a[i] = b[i];
		}
		cout << "Nhap so luong khung trang: ";
		cin >> frames;
	}
	return;
}

void FiFoAlgorithm(int* a, int pages, int frames)
{
	int pageFaults = 0;
	vector<string> arrfaults;
	int* table = new int[frames];
	fill_n(table, frames, -1);
	FOR(i, 0, pages)
	{
		int s = 0;
		FOR(j, 0, frames)
		{
			if (a[i] == table[j])
			{
				s++;
				pageFaults--;
			}
		}
		pageFaults++;
		if ((pageFaults <= frames) && (s == 0))
		{
			table[i] = a[i];
			arrfaults.push_back("*");
		}
		else if (s == 0)
		{
			table[(pageFaults - 1) % frames] = a[i];
			arrfaults.push_back("*");
		}
		else
		{
			arrfaults.push_back(" ");
		}
		cout << endl;
		FOR(j, 0, frames)
		{
			cout << table[j] << "\t";
		}
		cout << arrfaults[i];
	}
	cout << "\n\n Tong so loi trang = " << pageFaults;
	return;
}

void OPTAlgorithm(int* a, int pages, int frames)
{
	int* table = new int[frames];
	int* temp = new int[frames];
	bool* check = new bool[pages];
	vector<string> arrfaults;
	fill_n(table, frames, -1);
	fill_n(check, pages, true);
	int pageFaults = 0;
	FOR(i, 0, pages)
	{
		int s = 0;
		FOR(j, 0, frames)
		{
			if (table[j] == a[i])
			{
				s++;
				pageFaults--;
				arrfaults.push_back(" ");
				break;
			}
		}
		pageFaults++;
		if (pageFaults <= frames && s == 0)
		{
			table[pageFaults - 1] = a[i];
			arrfaults.push_back("*");
		}
		else
		{
			if (s == 0)
			{
				int pos, flag = 0;
				FOR(j, 0, frames)
				{
					temp[j] = -1;
					for (int k = i + 1; k < pages; ++k)
					{
						if (table[j] == a[k])
						{
							temp[j] = k;
							break;
						}
					}
				}
				FOR(k, 0, pages)
				{
					FOR(j, 0, frames)
					{
						if (temp[j] == -1 && check[k] && table[j] == a[k])
						{
							pos = j;
							flag = 1;
							check[k] = false;
							break;
						}
					}
					if (flag != 0)
						break;
				}
				if (flag == 0)
				{
					int max = temp[0];
					pos = 0;
					for (int j = 1; j < frames; ++j)
					{
						if (temp[j] > max)
						{
							max = temp[j];
							pos = j;
						}
					}
				}
				table[pos] = a[i];
				arrfaults.push_back("*");
			}
		}
		cout << endl;
		FOR(j, 0, frames)
		{
			cout << table[j] << "\t";
		}
		cout << arrfaults[i];
	}
	cout << "\n\n Tong so loi trang = " << pageFaults;
	return;
}

void LRUAlgorithm(int* a, int pages, int frames)
{
	int* table = new int[frames];
	bool* check = new bool[pages];
	vector<string> arrfaults;
	fill_n(table, frames, -1);
	fill_n(check, pages, true);
	int pageFaults = 0;
	FOR(i, 0, pages)
	{
		int s = 0;
		FOR(j, 0, frames)
		{
			if (table[j] == a[i])
			{
				s++;
				pageFaults--;
				arrfaults.push_back(" ");
				FOD(k, 0, i)
					if (a[k] == a[i])
					{
						check[k] = false;
						break;
					}
				break;
			}
		}
		pageFaults++;
		if (pageFaults <= frames && s == 0)
		{
			table[pageFaults - 1] = a[i];
			arrfaults.push_back("*");
		}
		else
		{
			if (s == 0)
			{
				int pos = -1;
				FOR(k, 0, pages)
				{
					FOR(j, 0, frames)
					{
						if (check[k] && table[j] == a[k])
						{
							pos = j;
							check[k] = false;
							break;
						}
					}
					if (pos != -1)
						break;
				}
				table[pos] = a[i];
				arrfaults.push_back("*");
			}
		}
		cout << endl;
		FOR(j, 0, frames)
		{
			cout << table[j] << "\t";
		}
		cout << arrfaults[i];
	}
	cout << "\n\n Tong so loi trang = " << pageFaults;
	return;
}

int main()
{
	int* arrpage, pages, frames;
	bool check = true;
	int choice;
	while (check)
	{
		cout << "\n\t===============Page Replacement algorithm===============";
		cout << "\n\t\t1.Default referenced sequence";
		cout << "\n\t\t2.Manual input sequence";
		cout << "\n\t\t3.Exit";
		cout << "\n\t===========================END==========================";
		cout << "\n\tNhap lua chon: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			Input(arrpage, pages, frames, 1);
			int choice1;
			bool check1 = true;
			while (check1)
			{
				cout << "\n\t==========Page Replacement algorithm==========";
				cout << "\n\t\t1. FIFO algorithm";
				cout << "\n\t\t2. OPT algorithm";
				cout << "\n\t\t3. LRU algorithm";
				cout << "\n\t\t4. Exit";
				cout << "\n\t====================END=======================";
				cout << "\n\tNhap lua chon: ";
				cin >> choice1;
				switch (choice1)
				{
				case 1:
					FiFoAlgorithm(arrpage, pages, frames);
					break;
				case 2:
					OPTAlgorithm(arrpage, pages, frames);
					break;
				case 3:
					LRUAlgorithm(arrpage, pages, frames);
					break;
				case 4:
					check1 = false;
					break;
				default:
					cout << "Lua chon khong hop le, vui long chon lai";
					break;
				}
			}
			break;
		}
		case 2:
		{
			Input(arrpage, pages, frames, 2);
			int choice2;
			bool check2 = true;
			while (check2)
			{
				cout << "\n\t==========Page Replacement algorithm==========";
				cout << "\n\t\t1. FIFO algorithm";
				cout << "\n\t\t2. OPT algorithm";
				cout << "\n\t\t3. LRU algorithm";
				cout << "\n\t\t4. Exit";
				cout << "\n\t====================END=======================";
				cout << "\n\tNhap lua chon: ";
				cin >> choice2;
				switch (choice2)
				{
				case 1:
					FiFoAlgorithm(arrpage, pages, frames);
					break;
				case 2:
					OPTAlgorithm(arrpage, pages, frames);
					break;
				case 3:
					LRUAlgorithm(arrpage, pages, frames);
					break;
				case 4:
					check2 = false;
					break;
				default:
					cout << "Lua chon khong hop le, vui long chon lai";
					break;
				}
			}
			break;
		}
		case 3:
			cout << "GOOD BYE!";
			check = false;
			break;
		default:
			cout << "Lua chon khong hop le, vui long chon lai";
			break;
		}
	}
}