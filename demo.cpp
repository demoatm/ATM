/*	Đồ án CTDL & GT : 
	Project 1: Mô phỏng ATM

- Thành viên :
		Võ Minh Tiến ( Nhóm trưởng )
		Le Hoài Thương
		Dương Triệu Lộc
		Trần Quang Nam
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include<conio.h>
#include <Windows.h>
#include<ctime>
using namespace std;
struct TaiKhoan
{
	string sID; 
	string sPIN;
	string sTen;
	int nMoney;
};
struct Node
{
	TaiKhoan xData;
	Node *pNext;
};
struct List
{
	Node *pHead, *pTail;
	List()
	{
		pHead = pTail = NULL;
	}
};
void textcolor(WORD color); // Ham đổi màu
void manhinhTB(string s);
string chuanhoaPass(string mk);//Hàm mã hóa mật khẩu
void docFile(List &L, int &nNum); // Đọc file
Node * createNode(TaiKhoan xAcc);// Tạo node
void addTail(List &L, TaiKhoan xAcc);// Thêm Node vào cuối ds
int chonCNGD(List L); // Hàm chọn chức năng GD
void ruttien(List L, Node *p,int nNum);// Hàm rút tiền
void updateDL(List &L, int nNum);// Cập nhật DL lên file
void xemthongtin(List L, Node *q);//Xem thông tin KH
void chuyenTien(List L, Node *q,int nNum);// Chuyển tiền
string kiemTraTime(string sX, Node * q); //Hàm lấy thời gian hệ thống
void ghiLSGD(List L, Node *q, Node *g, string sLoaiGD, int nTienGD);//Ghi lại LSGD lên file
void LichsuGD(Node *q);//In LSGD cua ID ra màn hình
void doimatkhau(List L, int nNum, Node *q);// Đổi mật khẩu
void Login(List L,int nNum);

int main()
{
	List L;
	int nNum = 0;
	docFile(L, nNum);
	Login(L,nNum);
	system("pause");
	return 0;
}
void Login(List L,int nNum)
{
	string sId = " "; 
	string sPin = " ";
	string sPass=" ";
	string sLuachon = " ";
	int nChon = 0;
	int nLan = 2;
	int j = 0;
	bool bFlag = 0;
	manhinhTB("login");
	textcolor(15);
	cout << "\t\t\tLuu y: Nhap ";
	textcolor(4);
	cout << "ESC";
	textcolor(7);
	cout << " de thoat khoi chuong trinh" << endl;
	while (j < 3&&bFlag==0)
	{
		textcolor(10);
		cout << "\n\t\tUser: ";
		rewind(stdin); getline(cin, sId);
		if (sId=="ESC"||sId=="esc")
		{
			manhinhTB("logout");
			textcolor(4);
			cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n";
			textcolor(121);
			break;
			
		}
		else
		{
			textcolor(10);
			cout << "\t\tPin:  ";
			sPin=chuanhoaPass(sPass);
			for (Node *p = L.pHead; p != NULL; p = p->pNext)
			{
				if (sId == p->xData.sID&&sPin == p->xData.sPIN)
				{
					bFlag = 1;
				cc:nChon = chonCNGD(L);
					switch (nChon)
					{
					case 1:
					{
						system("cls");
						manhinhTB("ruttien");
						ruttien(L, p, nNum);
						cout << "\n\t\t______________________________________________________________________\n";
						textcolor(9);
						cout << "\n\n\t\tNhap \"";
						textcolor(4);
						cout << "YES"; textcolor(9);
						cout << "\" de quay lai Menu. Nhap \"";
						textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin);
						getline(cin, sLuachon);
						if (sLuachon == "yes" || sLuachon == "YES" || sLuachon == "Yes")
						{
							goto cc;
						}
						else
						{
							manhinhTB("logout");
							textcolor(4);
							cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n\n\n";
							textcolor(15);
							break;
						}
					}
					case 2:
					{
						manhinhTB("chuyentien");
						chuyenTien(L, p, nNum);
						cout << "\n\t\t______________________________________________________________________\n";
						cout << "\n\n\t\tNhap \"";
						textcolor(4);
						cout << "YES"; textcolor(9);
						cout << "\" de quay lai Menu. Nhap \"";
						textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin);
						getline(cin, sLuachon);
						if (sLuachon == "yes" || sLuachon == "YES" || sLuachon == "Yes")
						{
							goto cc;
						}
						else
						{
							textcolor(4);
							cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n\n\n";
							textcolor(15);
							break;
						}
					}
					case 3:
					{
						xemthongtin(L, p);
						cout << "\n\t\t______________________________________________________________________\n";
						textcolor(9);
						cout << "\n\n\t\tNhap \"";
						textcolor(4);
						cout << "YES"; textcolor(9);
						cout << "\" de quay lai Menu. Nhap \"";
						textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin);
						getline(cin, sLuachon);
						if (sLuachon == "yes" || sLuachon == "YES" || sLuachon == "Yes")
						{
							goto cc;
						}
						else
						{
							manhinhTB("logout");
							textcolor(4);
							cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n\n\n";
							textcolor(15);
							break;
						}
					}
					case 4:
					{
						LichsuGD(p);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";
						textcolor(4);
						cout << "YES"; textcolor(9);
						cout << "\" de quay lai Menu. Nhap \"";
						textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin);
						getline(cin, sLuachon);
						if (sLuachon == "yes" || sLuachon == "YES" || sLuachon == "Yes")
						{
							goto cc;
						}
						else
						{
							manhinhTB("logout");
							textcolor(4);
							cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n\n\n";
							textcolor(15);
							break;
						}
					}
					case 5:
					{
						doimatkhau(L, nNum,p);
						cout << "\n\t\t______________________________________________________________________\n";
						textcolor(9);
						cout << "\n\n\t\t\tNhap \"";
						textcolor(4);
						cout << "YES"; textcolor(9);
						cout << "\" de quay lai Menu. Nhap \"";
						textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						rewind(stdin);
						getline(cin, sLuachon);
						if (sLuachon == "yes" || sLuachon == "YES" || sLuachon == "Yes")
						{
							goto cc;
						}
						else
						{
							manhinhTB("logout");
							textcolor(4);
							cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n\n\n";
							textcolor(15);
							break;
						}
					}
					
					case 6:
					{
						manhinhTB("logout");
						textcolor(4);
						cout << "\n\t\t\tCam on Quy khach da su dung Dich vu. Hen gap lai !\n\n\n";
						textcolor(15);
						break;
					}

					}

				}
	
			}
			j++;
			if (bFlag == 0)
			{
				system("cls");
				manhinhTB("login");
				textcolor(4);
				cout << "\t\tTai khoan hoac mat khau khong chinh xac.\a Con " << nLan-- << " lan dang nhap \n";
				if (j == 3)
				{
					system("cls");
					manhinhTB("login");
					textcolor(4);
					cout << "\t\tXin loi ban da nhap sai qua nhieu lan. He thong xin tu dong huy GD cua ban!\n\n\n\n\n";
					textcolor(10);
					break;

				}
			}

		}
	
		
	}
	
}
// Đổi mật khẩu
void doimatkhau(List L,int nNum, Node *q)
{
	system("cls");
	manhinhTB("doimatkhau");
	string a = " ";
	bool bFlag = 0;
	string sLuachon = "";
	string sPinNew = "";
	string sPinxn = "";
	string sPincu = "";
	textcolor(10);
	cout << "\t\t\tNhap lai PIN cu              : ";
	sPincu = chuanhoaPass(a);
	if (sPincu != q->xData.sPIN)
	{
		system("cls");
		manhinhTB("doimatkhau");
		textcolor(4);
		cout << "\n\t\t\tMat khau khong chinh xac. Xin vui long thu lai!";
	}
		else
		{
		
			do
			{

				textcolor(10);
				cout << "\n\t\t\tNhap ma PIN moi             : ";
				sPinNew = chuanhoaPass(a);
				textcolor(10);
				cout << "\n\t\t\tNhap lai ma PIN de xac nhan: ";
				sPinxn = chuanhoaPass(a);
				if (sPinNew == sPinxn)
				{
					textcolor(13);
					cout << "\n\n\t\t\tBan da thay doi ma PIN thanh cong!";
					bFlag = 1;
					q->xData.sPIN = sPinNew;
					updateDL(L,nNum);
				}
				else
				{
					system("cls");
					manhinhTB("doimatkhau");
					textcolor(4);
					cout << "\t\t\tMa PIN moi khong trung nhau. Xin vui long thu lai!";

				}
			} while (bFlag==0);

		}


	
}
// Ghi lại lịch sử GD
void ghiLSGD(List L, Node *q, Node *g, string sLoaiGD, int nTienGD)
{
	
	errno_t err;
	struct tm time_info;
	time_t time_create = time(NULL);
	localtime_s(&time_info, &time_create);
	char timebuf[26];
	err = asctime_s(timebuf, 26, &time_info);

	ofstream fcout;
	fcout.open(q->xData.sID + ".txt", ios::app);
	if (sLoaiGD=="ruttien")
	{
		fcout << "!"<<kiemTraTime("dd", q) << time_info.tm_mday << "-" << kiemTraTime("mm", q) << 1 + time_info.tm_mon << "-" << 1900 + time_info.tm_year << "           " << kiemTraTime("hh", q)
			<< time_info.tm_hour << ":" << kiemTraTime("m", q) << time_info.tm_min << ":" << kiemTraTime("ss", q) << time_info.tm_sec << "           "
			<< "RUT TIEN    " << "           " << kiemTraTime("100",q)<< nTienGD <<" VND"<< "           " << "    NULL     " <<"        "<<"   NULL" << endl;
	}
	else if (sLoaiGD=="chuyentien")
	{
		fcout << "!"<<kiemTraTime("dd", q) << time_info.tm_mday << "-" << kiemTraTime("mm", q) << 1 + time_info.tm_mon << "-" << 1900 + time_info.tm_year << "           " << kiemTraTime("hh", q)
			<< time_info.tm_hour << ":" << kiemTraTime("m", q) << time_info.tm_min << ":" << kiemTraTime("ss", q) << time_info.tm_sec << "           "
			<< "CHUYEN TIEN " << "           " << kiemTraTime("100", g) << nTienGD << " VND" << "           " << g->xData.sID <<"           "<<g->xData.sTen << endl;
	}
	else if (sLoaiGD=="nhantien")
	{
		fcout << "!" << kiemTraTime("dd", q) << time_info.tm_mday << "-" << kiemTraTime("mm", q) << 1 + time_info.tm_mon << "-" << 1900 + time_info.tm_year << "           " << kiemTraTime("hh", q)
			<< time_info.tm_hour << ":" << kiemTraTime("m", q) << time_info.tm_min << ":" << kiemTraTime("ss", q) << time_info.tm_sec << "           "
			<< "NHAN TIEN  " << "           " << kiemTraTime("100", q) << nTienGD << " VND" << "           " << g->xData.sID << "           " << g->xData.sTen <<endl;
	}			
}
//Xem lịch sử GD trên màn hình
void LichsuGD(Node *q)
{;
	
	string sLSGD = " ";
	
	manhinhTB("lsgd");
	cout << "\n[ Date ]" << "         " << "    [ Time ]" << "      " << "    [ Loai GD ]" << "        " << "  [ So tien GD ]" << " "<<"       [ Account Number ]"<< " " <<"       [ Ten Chu The ]\n";
	
	ifstream fcin;
	fcin.open(q->xData.sID + ".txt");
	textcolor(15);
	while (!fcin.eof())
	{
		
		rewind(stdin); getline(fcin, sLSGD, '!');
		cout << sLSGD << endl;
	
	}
	
	cout << "\t\t______________________________________________________________________________________________________\n";
	fcin.close();

}
// Chuyển thời gian về dạng dd/mm/yy
string kiemTraTime(string sX, Node * q)
{
	
	errno_t err;
	struct tm time_info;
	time_t time_create = time(NULL);
	localtime_s(&time_info, &time_create);
	char timebuf[26];
	err = asctime_s(timebuf, 26, &time_info);
	if (sX == "ss")
	{
		if (time_info.tm_sec < 10)
		{
			return "0";
		}
	}
	if (sX == "m")
	{
		if ((time_info.tm_min) < 10)
		{
			return "0";
		}
	}
	if (sX == "hh")
	{
		if (time_info.tm_hour < 10)
		{
			return "0";
		}
	}
	if (sX == "dd")
	{
		if (time_info.tm_mday < 10)
		{
			return "0";
		}
	}
	if (sX == "mm")
	{
		if (time_info.tm_mon + 1 < 10)
		{
			return "0";
		}
	}
	if (sX == "100")
	{
		if (q->xData.nMoney < 100000)
		{
			return " ";
		}
	}
	return "";
	return "";
}
//Chuyển tiền
void chuyenTien(List L, Node *q,int nNum)
{
	manhinhTB("chuyentien");
	int nTiensent = 0;
	int bFlag = 0;
	string sSoTK = " ";
	while (bFlag == 0)
	{
		textcolor(10);
		cout << "\t\t\tNhap so Tai khoan thu huong   :    ";
		textcolor(15);
		rewind(stdin);
		getline(cin, sSoTK);
		for (Node *p = L.pHead; p != NULL; p = p->pNext)
		{
			if (sSoTK == p->xData.sID & sSoTK != q->xData.sID)
			{
				do
				{
					textcolor(10);
					cout << "\t\t\tNhap So tien can chuyen       :    ";
					textcolor(15);
					cin >> nTiensent;
					if (nTiensent < 50000)
					{
						manhinhTB("chuyentien");
						textcolor(124);
						cout << "\t\t\t\tSo tien can chuyen > 50.000 VND !\n";
					}
					else if (nTiensent > q->xData.nMoney - 50000)
					{
						system("cls");
						manhinhTB("chuyentien");
						textcolor(124);
						cout << "\t\t\tSo tien vuot qua so du, xin moi nhap lai !\n";
					}
				} while (nTiensent < 50000 || nTiensent > q->xData.nMoney - 50000);
				string sPin = " ";
				string a = " ";
				do
				{
					textcolor(10);
					cout << "\t\t\tNhap lai ma Pin de xac nhan GD:    ";
					textcolor(15);
					
					sPin = chuanhoaPass(a);
					if (sPin == q->xData.sPIN)
					{
						bFlag = 1;
						textcolor(13);
						cout << "\n\n\t\t\tBan da CHUYEN TIEN thanh cong. So du con lai la: ";
						cout << q->xData.nMoney - nTiensent << " VND !\n";
						textcolor(9);
						q->xData.nMoney = q->xData.nMoney - nTiensent;
						p->xData.nMoney = p->xData.nMoney + nTiensent;
						updateDL(L, nNum);
						ghiLSGD(L, q, p, "chuyentien", nTiensent);
						ghiLSGD(L, p, q, "nhantien", nTiensent);

						break;
					}
					else
					{
						manhinhTB("chuyentien");
						textcolor(4);
						cout << "\t\t\tMat khau khong chinh xac, vui long Kiem Tra lai !\n";
					}
				} while (sPin != p->xData.sPIN);
				break;
			}
			
			else
			{
				bFlag = 0;
			}
		}
		if (bFlag==0)
		{
			manhinhTB("chuyentien");
			textcolor(4);
			cout << "\t\t\tSo tai khoan khong chinh xac. Vui long nhap lai!\n";
		}
	}
}
// Xem thông tin TK
void xemthongtin(List L, Node *q)
{
	manhinhTB("xemthongtin");
	textcolor(124);
	cout << "\n";
	cout << "\t\t\tHo va Ten:	 " << q->xData.sTen << endl;
	cout << "\t\t\tSo Tai Khoan:    " << q->xData.sID << endl;
	cout << "\t\t\tSo Du Tai Khoan: " << q->xData.nMoney << " VND";
		
}
//Hàm rút tiền
void ruttien(List L, Node *p,int nNum)
{
	Node *g = NULL;
	string sPin = " ";
	string a = " ";
	int nSotiencanrut = 0;
	do 
	{
	dd: textcolor(10);
		cout << "\t\tNhap so tien can rut          : ";
		textcolor(15);
		cin >> nSotiencanrut; 
		if (nSotiencanrut < 50000)
		{
			system("cls");
			manhinhTB("ruttien");
			textcolor(4);
			cout << "\t\t\tSo tien can rut phai > 50.000vnd!\n";
			
		}
		else if (nSotiencanrut > p->xData.nMoney||nSotiencanrut> p->xData.nMoney-50000)
		{
			system("cls");
			manhinhTB("ruttien");
			textcolor(4);
			cout << "\t\t\tSo tien vuot qua so du, xin moi nhap lai !\n";
			
		}
	} while (nSotiencanrut < 50000 || p->xData.nMoney < 50000||nSotiencanrut > p->xData.nMoney|| nSotiencanrut>p->xData.nMoney - 50000);
	do
	{
	textcolor(10);
	cout << "\t\tNhap lai ma Pin de xac nhan GD: ";
	textcolor(15);
	sPin = chuanhoaPass(a);
	if (sPin==p->xData.sPIN)
	{
		textcolor(13);
		cout << "\n\n\t\t\tBan da RUT TIEN thanh cong. So du con lai la: ";
		cout << p->xData.nMoney - nSotiencanrut << " VND";
		p->xData.nMoney = p->xData.nMoney - nSotiencanrut;
		updateDL(L, nNum);
		ghiLSGD(L, p, g, "ruttien", nSotiencanrut);
		break;
	}
		system("cls");
		manhinhTB("ruttien");
		textcolor(4);
		cout << "\t\t\tMat khau khong chinh xac, vui long Kiem Tra lai !\n";
	} while (true);
}
//Cập nhật lại dữ liệu
void updateDL(List &L,int nNum)
{
	ofstream fcout;
	fcout.open("TheTu.dat", ios::out);
	fcout << nNum << endl;
	for (Node *p=L.pHead;p!=NULL;p=p->pNext)
	{
		fcout << p->xData.sID << "#";
		fcout << p->xData.sPIN << "#";
		fcout << p->xData.sTen << "#";
		fcout << p->xData.nMoney << endl;
	}
	fcout.close();
}
// Màn hình khi Login thành công
int chonCNGD(List L)
{
	int nChon = 0;
	manhinhTB("chongd");
	do 
	{
		textcolor(82);
		cout << "\t\t\tNhap so de thuc hien: ";
		cin >> nChon;
		if (nChon > 6 || nChon < 1)
		{
			system("cls");
			manhinhTB("chongd");
		}
	}while (nChon > 6 || nChon < 1);
	
		

	return nChon;

}
// Hàm đọc DL từ file lên
void docFile(List &L, int &nNum)
{
	TaiKhoan xAcc;
	ifstream fcin;
	fcin.open("TheTu.dat", ios::in);
	fcin >> nNum;
	fcin.ignore(1);
	for (int i = 0; i < nNum; i++)
	{
		rewind(stdin); getline(fcin, xAcc.sID, '#');
		rewind(stdin); getline(fcin, xAcc.sPIN, '#');
		rewind(stdin); getline(fcin, xAcc.sTen, '#');
		fcin >> xAcc.nMoney; fcin.ignore(1);
		addTail(L, xAcc);
	}
	fcin.close();
}
Node * createNode(TaiKhoan xAcc)
{
	Node *p = new Node;
	if (p==NULL)
	{
		exit(1);
	}
	else
	{
		p->xData = xAcc;
		p->pNext = NULL;
		return p;
	}
	
}
void addTail(List &L, TaiKhoan xAcc)
{
	Node *pNew = createNode(xAcc);
	if (L.pHead == NULL)
	{
		L.pHead = L.pTail = pNew;
		
	}
	
		L.pTail->pNext = pNew;
		L.pTail = pNew;
	
}
// Hàm chuyển màu chữ
void textcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//Hàm mã hóa password
string chuanhoaPass(string mk)
{
	string sPass = "";
	
	char ch;
	int dem = 0;
	char pass[10];
	while ((ch = _getch()) != 13) {
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9')) {
			printf("*");
			pass[dem++] = ch;
			sPass.push_back(ch);
			
			
		}
		else
			if (ch == 8)
				if (dem > 0) {
					printf("\b \b");
					dem--;
				}
		if (ch=='\n')
		{
			break;
		}
	}
	pass[dem] = 0;
	return sPass;
}
//Hàm viền Thông báo
void manhinhTB(string s)
{
	if (s == "login")
	{
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *         ";
		textcolor(10);
		cout << " DANG NHAP HE THONG           ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
	}
	else if (s=="logout")
	{
		system("cls");
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *         ";
		textcolor(10);
		cout << " DANG XUAT HE THONG           ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
	}
	else if (s=="doimatkhau")
	{
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *              ";
		textcolor(10);
		cout << "DOI MAT KHAU             ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
	}
	else if (s=="chongd")
	{
		system("cls");
		textcolor(10);
		cout << "\n\t\t\t\t\tLOGIN THANH CONG !\n\n";
		textcolor(6);
		cout << "\t\t*************************************************************************" << endl;
		cout << "\t\t*  ";
		textcolor(10);
		cout << "\t\t    CHON CHUC NANG DE THUC HIEN"; textcolor(6);
		cout << "\t\t\t\t*" << endl;
		textcolor(6);
		cout << "\t\t*  ";
		textcolor(10);
		cout << "   1. Rut Tien\t\t\t2. Chuyen Tien"; textcolor(6);
		cout << "   \t\t*" << endl;
		textcolor(6);
		cout << "\t\t*  ";
		textcolor(10);
		cout << "   3. Thong Tin Tai Khoan\t\t4. Lich su giao dich"; textcolor(6);
		cout << "   \t\t*" << endl;
		textcolor(6);
		cout << "\t\t*  ";
		textcolor(10);
		cout << "   5. Doi Mat Khau \t\t\t6. Thoat giao dich      "; textcolor(6);
		cout << "   \t*" << endl;
		cout << "\t\t*************************************************************************" << endl;
	}
	else if (s == "ruttien")
	{
		
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *              ";
		textcolor(10);
		cout << "RUT TIEN                 ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		
	}
	else if (s == "chuyentien")
	{
		system("cls");
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *              ";
		textcolor(10);
		cout << "CHUYEN TIEN              ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";	
	}
	else if (s=="xemthongtin")
	{
		system("cls");
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *          ";
		textcolor(10);
		cout << "THONG TIN KHACH HANG         ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
	}
	else if (s=="lsgd")
	{
		system("cls");
		textcolor(11);
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
		cout << "\t\t\t  *          ";
		textcolor(10);
		cout << "LICH SU GIAO DICH            ";
		textcolor(11);
		cout << "*\n";
		cout << "\t\t\t  * * * * * * * * * * * * * * * * * * * * *\n";
	}
}