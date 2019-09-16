#include <regex>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

static const int kTextSize = 10;

void nuancePbSegment(unsigned char * infile, unsigned char * outfile)
{
	string str_in;
	cout << infile << endl;
	cout << outfile <<endl;
    ofstream out;//输出文件
    out.open((const char *)outfile);
    if (out.is_open())
    {
        out << "This is a line.\n";
        out << "This is another line.\n";
        
    }
    char buffer[10000];
    ifstream in((const char *)infile);//读文件
    if (!in.is_open())
    {
        cout << "error!";
        getchar();//让dos停留观测结果用，可删除
        exit(1);
    }
    while (!in.eof())
    {
        in.getline(buffer, 1000);
		str_in = buffer;
		cout << str_in <<endl;
		cout << str_in.find("Contact_ID") <<endl;
		out << buffer <<endl;
    }
	out.close();

    //第一种存储方式
    //match_results<string::const_iterator> result;
    //第二种存储方式
    smatch result;

    //文本数据
    string str="1994 is my birth year 1994";
    //正则表达式
    string regex_str("\\d{4}");
    regex pattern1(regex_str,regex::icase);

    //迭代器声明
    string::const_iterator iter = str.begin();
    string::const_iterator iterEnd= str.end();
    string temp;
    //正则查找
    while (std::regex_search(iter,iterEnd,result,pattern1))
    {
        temp=result[0];
        cout<<temp<<endl;
        iter = result[0].second; //更新搜索起始位置
    }

    //正则匹配
    string regex_str2("(\\d{4}).*");
    regex pattern2(regex_str2,regex::icase);

    if(regex_match(str,result,pattern2)){
        cout<<result[0]<<endl;
        cout<<result[1]<<endl;
    }
    
    //正则替换
    std::regex reg1("\\d{4}");
    string t("1993");
    str = regex_replace(str,reg1,t); //trim_left
    cout<<str<<endl;

}

 
std::wstring s2ws(const std::string& str) {
  if (str.empty()) {
    return L"";
  }
  unsigned len = str.size() + 1;
  setlocale(LC_CTYPE, "");
  wchar_t *p = new wchar_t[len];
  mbstowcs(p, str.c_str(), len);
  std::wstring w_str(p);
  delete[] p;
  return w_str;
}
 
std::string ws2s(const std::wstring& w_str) {
    if (w_str.empty()) {
      return "";
    }
    unsigned len = w_str.size() * 4 + 1;
    setlocale(LC_CTYPE, "");
    char *p = new char[len];
    wcstombs(p, w_str.c_str(), len);
    std::string str(p);
    delete[] p;
    return str;
}
 
 
bool FormatText(std::string* txt) {
  if (NULL == txt) {
    return false;
  }
  std::cout << "before:" << *txt << std::endl;
  std::wstring w_txt = s2ws(*txt);
  std::cout << "wstring size:" << w_txt.size() << std::endl;
  std::cout << "string size:" << (*txt).size() << std::endl;
  if (w_txt.size() > kTextSize) {
    w_txt = w_txt.substr(0, kTextSize);
    *txt = ws2s(w_txt);
    *txt += "...";
  }
  std::cout << "after:" << *txt << std::endl;
  return true;
}

int main()
{
    unsigned char infile[] = "D:\\Projects\\CPhoneBookExtend\\smartPhoneBook\\phonebook_foryou.cop";
    unsigned char outfile[] = "D:\\Projects\\CPhoneBookExtend\\smartPhoneBook\\phonebook_foryou_result_c.cop";

    //nuancePbSegment((unsigned char *)infile, (unsigned char *)outfile);
	assert(L"" == s2ws(""));
 
	std::string txt = "龙之谷app好玩等你";
	assert(24 == txt.size());
	std::wstring w_txt = s2ws(txt);
	assert(10 == w_txt.size());
 
	assert("" == ws2s(L""));
 
	w_txt = L"龙之谷app好玩等你";
	assert(10 == w_txt.size());
	txt = ws2s(w_txt);
	assert(24 == txt.size());
 
	txt = "龙之谷app公测开启";
	std::string format_txt = txt;
	FormatText(&format_txt);
	assert(txt == format_txt);
 
	txt = "龙之谷app公测火爆开启";
	FormatText(&txt);
	format_txt = "龙之谷app公测火爆...";
	assert(format_txt == txt);
	system("pause");
    return 0;
}