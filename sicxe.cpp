#include<iostream>
#include<map>
#include<utility>
#include<cmath>
#include<vector>
#include<set>
#include<stdio.h>
#include<ctype.h>
#include<iomanip>
#include<fstream>
#include<algorithm>
#include<queue>
using namespace std;

class SYMTAB;
class LITTAB;
class OPPTAB;
class LOCCTR;
vector<string *> the_list;

int hex_map(char c)
{
	if(c=='A' || c=='a') return 10;
	else if(c=='B' || c=='b') return 11;
	else if(c=='C' || c=='c') return 12;
	else if(c=='D' || c=='d') return 13;
	else if(c=='E' || c=='e') return 14;
	else if(c=='F' || c=='f') return 15;
	else if(c=='0') return 0;
	else if(c=='1') return 1;
	else if(c=='2') return 2;
	else if(c=='3') return 3;
	else if(c=='4') return 4;
	else if(c=='5') return 5;
	else if(c=='6') return 6;
	else if(c=='7') return 7;
	else if(c=='8') return 8;
	else if(c=='9') return 9;
}

int hex_to_dec(string s)
{
	int num=0,temp=0,j=0;
	for(int i=s.length()-1;i>=0;i--)
	{
		num+=hex_map(s[i])*pow(16,j++);
	}
	return num;
}

char dec_map(int n)
{
	if(n==1) return '1';
	else if(n==2) return '2';
	else if(n==3) return '3';
	else if(n==4) return '4';
	else if(n==5) return '5';
	else if(n==6) return '6';
	else if(n==7) return '7';
	else if(n==8) return '8';
	else if(n==9) return '9';
	else if(n==0) return '0';
	else if(n==10) return 'A';
	else if(n==11) return 'B';
	else if(n==12) return 'C';
	else if(n==13) return 'D';
	else if(n==14) return 'E';
	else if(n==15) return 'F';
}

string dec_to_hex(int num)
{
	char t1;
	int t2;
	string temp="";
	int rem=0;
	if(num<0)
		t2=abs(num);
	else
		t2=num;
	while(t2)
	{
		rem=t2%16;
		t2/=16;
		temp+=dec_map(rem);
	}
	if(num<0){
		if(temp.size()<=3)
		while(temp.size()!=3){
		temp+='0';
		}	
	}
	for(int i=0,j=temp.length()-1;i<j;i++,j--)
	{
		t1=temp[i];
		temp[i]=temp[j];
		temp[j]=t1;
	}
	if(num<0){
		for(int i=0;i<3;i++){
			if(i==2)
				temp[i]=dec_map(16-hex_map(temp[i]));
			else
				temp[i]=dec_map(15-hex_map(temp[i]));
		}
	}
	return temp;
}

int str_to_dec(string s)
{
	int temp=0,num=0,j=0;
	for(int i=s.length()-1;i>=0;i--,j++)
	{
		temp=hex_map(s[i]);	
		if(temp==0) continue;
		num+=temp*pow(10,j);
	}
	return num;	
}

string dec_to_str(int dec)
{	
	int r,i,j;
	char temp;
	string res="";
	while(dec!=0)
	{
		r=dec%10;
		dec/=10;
		res+=char(r+48);
	}
	for(i=0,j=res.length()-1;i<j;i++,j--)
	{
		temp=res[i];
		res[i]=res[j];
		res[j]=temp;
	}
	return res;
}

string gen_data(string oper)
{
	string data="";
	if(oper[0]=='C' && oper[1]==39)
	{
		for(short i=2;oper[i]!=39;i++)
		{
			data+=dec_to_hex(int(oper[i]));
		}
	}
	else if(oper[0]=='X' && oper[1]==39)
	{
		for(short i=2;oper[i]!=39;i++)
		{
			data+=oper[i];
		}
	}
	else {
		data=dec_to_hex(str_to_dec(oper));
	}
	return data;	
}

int size_of_data(string oper)
{
	unsigned int size=0;
	if(oper[0]=='C' && oper[1]==39)
	{
		for(short i=2;oper[i]!=39;i++)
		{
			size++;
		}
	}
	else if(oper[0]=='X' && oper[1]==39)
	{
		for(short i=2;oper[i]!=39;i=i+2)
		{
			size++;
		}
	}
	else size+=3;
	return size;
}


string hex_sub(string s1,string s2)
{
	int temp1=hex_to_dec(s1);
	int temp2=hex_to_dec(s2);
	return dec_to_hex(temp1-temp2);
}

vector<string> split(char *b)
{	
	bool flag=false;
	vector<string> vec;
	string data="";
	for(short i=0;i<30;i++)
	{
		if(isalnum(b[i]) || b[i]=='+' || b[i]=='@' || b[i]=='#' || b[i]=='=' || b[i]==',' || b[i]==39 ) 
		{
			data+=b[i];
			flag=true;
		}
		else if((b[i]==' ' || b[i]=='\n') && flag) 
		{
			vec.push_back(data);
			data.clear();
			flag=false;
		} 
	}
	return vec;
}

char map_reg(string c)
{
		if(c=="A")		
			return '0';
		else if(c=="X")		
			return '1';
		else if(c=="L")		
			return '2';
		else if(c=="PC")	
			return '8';
		else if(c=="SW")	
			return '9';
		else if(c=="B")		
			return '3';
		else if(c=="S")		
			return '4';
		else if(c=="T")		
			return '5';
		else if(c=="F")		
			return '6';
}

void get_reg(string sym,string &r1,string &r2)
{	
	bool flag=false;
	r1.clear();
	r2.clear();
	for(short i=0;i<sym.length();i++)
	{
		if(sym[i]==',') 
		{
		flag=true;
		continue;
		}
		if(flag==false)		
			r1+=sym[i];
		else
			r2+=sym[i];		
	}	
} 

string concate_zero(string sym,int size)
{
	reverse(sym.begin(),sym.end());
	while(sym.length()<size){	
		sym+='0';
	}
	reverse(sym.begin(),sym.end());
	return sym;
}

class LOCCTR                                                           //location counter defination             
{
	int loc_int;
	string loc_str;
	public:
		LOCCTR()
		{
			loc_int=0;
			loc_str="0000";
		}
		void set(string);
		void add(int n);
		string fetch_loc();
}loc_counter;

void LOCCTR::set(string s)
{
	loc_str=s;//
	loc_int=hex_to_dec(s);
}

void LOCCTR::add(int n)
{
	loc_int+=n;
	loc_str=dec_to_hex(loc_int);
}

string LOCCTR::fetch_loc()
{
	return loc_str;
}

class OPPTAB                                                               //opptab defination
{	
	map<string,pair<string,int> > opptab;
	
	public:
	OPPTAB()
	{
		opp_tab_fill();
	}
	
	void opp_tab_fill();
	string fetch(string s);	
	int get_addr_mode(string opp);
	int isPresent(string sym);
	
}opp_table;

void OPPTAB::opp_tab_fill()
{
	opptab["ADD"]=pair<string,int>("18",3);
	opptab["ADDF"]=pair<string,int>("58",3);
	opptab["ADDR"]=pair<string,int>("90",2);
	opptab["AND"]=pair<string,int>("40",3);
	opptab["CLEAR"]=pair<string,int>("B4",2);
	opptab["COMP"]=pair<string,int>("28",3);
	opptab["COMPF"]=pair<string,int>("88",3);
	opptab["COMPR"]=pair<string,int>("A0",2);
	opptab["DIV"]=pair<string,int>("24",3);
	opptab["DIVF"]=pair<string,int>("64",3);
	opptab["DIVR"]=pair<string,int>("9C",2);
	opptab["FIX"]=pair<string,int>("C4",1);
	opptab["FLOAT"]=pair<string,int>("C0",1);
	opptab["HIO"]=pair<string,int>("F4",1);
	opptab["J"]=pair<string,int>("3C",3);
	opptab["JEQ"]=pair<string,int>("30",3);
	opptab["JGT"]=pair<string,int>("34",3);
	opptab["JLT"]=pair<string,int>("38",3);
	opptab["JSUB"]=pair<string,int>("48",3);
	opptab["LDA"]=pair<string,int>("00",3);
	opptab["LDB"]=pair<string,int>("68",3);
	opptab["LDCH"]=pair<string,int>("50",3);
	opptab["LDF"]=pair<string,int>("70",3);
	opptab["LDL"]=pair<string,int>("08",3);
	opptab["LDS"]=pair<string,int>("6C",3);
	opptab["LDT"]=pair<string,int>("74",3);
	opptab["LDX"]=pair<string,int>("04",3);
	opptab["LPS"]=pair<string,int>("D0",3);
	opptab["MUL"]=pair<string,int>("20",3);
	opptab["MULF"]=pair<string,int>("60",3);
	opptab["MULR"]=pair<string,int>("98",2);
	opptab["NORM"]=pair<string,int>("C8",1);
	opptab["OR"]=pair<string,int>("44",3);
	opptab["RD"]=pair<string,int>("D8",3);
	opptab["RMO"]=pair<string,int>("AC",2);
	opptab["RSUB"]=pair<string,int>("4C",3);
	opptab["SHIFTL"]=pair<string,int>("A4",2);
	opptab["SHIFTR"]=pair<string,int>("A8",2);
	opptab["SIO"]=pair<string,int>("F0",1);
	opptab["SSK"]=pair<string,int>("EC",3);
	opptab["STA"]=pair<string,int>("0C",3);
	opptab["STB"]=pair<string,int>("78",3);
	opptab["STCH"]=pair<string,int>("54",3);
	opptab["STF"]=pair<string,int>("80",3);
	opptab["STI"]=pair<string,int>("D4",3);
	opptab["STL"]=pair<string,int>("14",3);
	opptab["STS"]=pair<string,int>("7C",3);
	opptab["STSW"]=pair<string,int>("E8",3);
	opptab["STT"]=pair<string,int>("84",3);
	opptab["STX"]=pair<string,int>("10",3);
	opptab["SUB"]=pair<string,int>("1C",3);
	opptab["SUBF"]=pair<string,int>("5C",3);
	opptab["SUBR"]=pair<string,int>("94",2);
	opptab["SVC"]=pair<string,int>("B0",2);
	opptab["TD"]=pair<string,int>("E0",3);
	opptab["TIO"]=pair<string,int>("F8",1);
	opptab["TIX"]=pair<string,int>("2C",3);
	opptab["TIXR"]=pair<string,int>("B8",2);
	opptab["WD"]=pair<string,int>("DC",3);
}

string OPPTAB::fetch(string key)
{
	if(opptab.count(key)) return opptab[key].first;
	else return "const";
}

int OPPTAB::get_addr_mode(string opp)
{
	if(opp_table.opptab.count(opp)) return opp_table.opptab[opp].second;
	else return 0;
}

int OPPTAB::isPresent(string sym){
	return opptab.count(sym);
}

class SYMTAB                                                            //symbol table defination
{
	public:
	map<string,string> symtab;
	set<string> duplicate;
	
	void set_dup(string sym);
	void show_sym();
}sym_table;

void SYMTAB::show_sym()
{
	cout<<"\nsymbols:::\n";
	map<string,string> ::iterator it;
	for(it=symtab.begin();it!=symtab.end();it++)
	{
		cout<<it->first<<"-->> "<<it->second<<endl;
	}
	cout<<endl;
}

void SYMTAB::set_dup(string sym)
{	
	duplicate.insert(sym);
}

class LITTAB
{
	public:
	map<string,string> littab;
	vector<string> litlist;
	void insert_lit(string lit);
	void fill_up();
	void show_lit();
	
	
}lit_table;

void LITTAB::show_lit()
{
	cout<<"\nliterals:::\n";
	map<string,string> ::iterator it;
	for(it=littab.begin();it!=littab.end();it++)
	{
		cout<<it->first<<"-->> "<<it->second<<endl;
	}
	cout<<endl;
}

void LITTAB::insert_lit(string lit)
{
	litlist.push_back(lit);
}

void LITTAB::fill_up()
{
	for(int i=0;i<litlist.size();i++)
	{
		string * temp=new string[5];
		temp[0]=loc_counter.fetch_loc();
		temp[1]="*";
		temp[2]=litlist[i];
		temp[3]="";
		temp[4]="";
		the_list.push_back(temp);
		littab[litlist[i]]=loc_counter.fetch_loc();
		loc_counter.add(size_of_data(litlist[i]));
	}
	litlist.clear();
}

short ins_format=3;
string prog_name="";
string prog_length="";
string start_addr="";
queue<string> text_break;
vector<string> modi_rec;
int cnt=0;

void pass1(FILE *fp)                                                                //pass 1 function defination
{
	unsigned int line_no=0;
	string label,symbol,opp;
	char addr_mode;
	char buffer[30];
	bool flag=false;
	int j=0;
	vector<string> vec;
	while(fgetc(fp)!=EOF)	
	{	
		string* temp=new string[5];
		for(int i=0;i<30;i++){
			buffer[i]='$';
		}
		if(fgetc(fp)==EOF) break;
		fseek(fp,-2,SEEK_CUR);
		
		fgets(buffer,30,fp);
		if(buffer[0]=='.')
			continue;
		vec.erase(vec.begin(),vec.end());
		label.clear();
		symbol.clear();
		opp.clear();
		addr_mode=' ';
		vec=split(buffer);
		if(vec.size()==3){
			label=vec[0];
			opp=vec[1];
			symbol=vec[2];	
		}
		else if(vec.size()==2){
			opp=vec[0];
			symbol=vec[1];
		}
		else if(vec.size()==1){
			opp=vec[0];
		}
		if((opp=="RESW" || opp=="RESB")&& !flag){
			flag=true;
			text_break.push(concate_zero(the_list[j-1][0],6));	
		}
		if(opp!="LTORG" && opp!="RESW" && opp!="RESB" && opp!="START" && opp!="END" ){
			flag=false;
			temp[0]=loc_counter.fetch_loc();
			temp[1]=label;
			temp[2]=opp;
			temp[3]=symbol;
			temp[4]="";
			the_list.push_back(temp);
			j++;
		}
		if(opp[0]=='+'){
			ins_format=4;
			opp.erase(opp.begin());
		}
		else ins_format=opp_table.get_addr_mode(opp);
		if(symbol[0]=='@' || symbol[0]=='#' || symbol[0]=='='){
			addr_mode=symbol[0];
			symbol.erase(symbol.begin());
		}
		if(opp=="END") break;
		if(opp=="LTORG") 
		{
			lit_table.fill_up();
			line_no++;
			continue;
		}
		if(opp=="START"){
			start_addr="000000";
			prog_name=label;
			continue;
		}	
		if(addr_mode=='=') 
		{
			lit_table.litlist.push_back(symbol);
		}
		
		if(!label.empty())
		{
			if(sym_table.symtab.count(label)) 
			{
				cout<<"\nDUPLICATE SYMBOL:::"<<label<<" DEFINED AT LINE::"<<line_no<<endl;
				sym_table.duplicate.insert(label);
			}
			else 
				sym_table.symtab[label]=loc_counter.fetch_loc(); 
			
		}
		
		if(!opp.empty())
		{
			if(opp_table.isPresent(opp)) 
				loc_counter.add(ins_format);
			else if(opp=="RESW") 
				loc_counter.add(3*str_to_dec(symbol));
			else if(opp=="RESB") 
				loc_counter.add(str_to_dec(symbol));
			else if(opp=="WORD") 
				loc_counter.add(3);
			else if(opp=="BYTE") 
				loc_counter.add(size_of_data(symbol));
			else if(opp=="BASE")
				continue;
			else 
				cout<<"\nINVALID OPERATION CODE:::"<<opp<<" AT LINE::"<<line_no<<endl;
		}
		line_no++;
	}
	lit_table.fill_up();
	prog_length=(loc_counter.fetch_loc());
	prog_length=concate_zero(prog_length,6);
	cout<<"program "<<prog_name<<" of length: "<<prog_length<<endl;
	fclose(fp);	
}


void pass2()	                                                        //pass 2 function defination
{
	string objcode="",opcode="";
	int addr_mode=3;
	char flag_bit;
	bool rel=true;
	string base_addr="";
	for(int i=0;i<the_list.size();i++){
		//flags setting::::::::::::::::::::://
		addr_mode=3;
		objcode.clear();
		opcode.clear();
		try{
			if(the_list[i][2]=="BASE")	
				rel=false;
			if(the_list[i][1]=="*"){
				the_list[i][4]=gen_data(the_list[i][2]);
				continue;
			}
			if(the_list[i][2][0]=='+'){
				ins_format=4;
				modi_rec.push_back(dec_to_hex(hex_to_dec(the_list[i][0])+1));
				the_list[i][2].erase(the_list[i][2].begin());
			}
			else
				ins_format=3;
			if(the_list[i][3][0]=='#'){
				addr_mode=1;
				the_list[i][3].erase(the_list[i][3].begin());
			}
			else if(the_list[i][3][0]=='@'){
				addr_mode=2;
				the_list[i][3].erase(the_list[i][3].begin());
			}
			if(opp_table.get_addr_mode(the_list[i][2])!=2 && *the_list[i][3].end()=='X' && *(the_list[i][3].end()-1)==','){
				if(ins_format==4)
					flag_bit='9';
				else
					flag_bit='A';
			}
			else{
				if(ins_format==4)
					flag_bit='1';
				else
					flag_bit='2';
			}
			if(the_list[i][3][0]=='=')
				the_list[i][3].erase(the_list[i][3].begin());
			}
			
		catch(...){
			cout<<"block one\n";
		}
		//::::::::::::::::::Assigning objectcodes:::::::::::::::::://
		try{	
			if(the_list[i][2]!="BYTE" && the_list[i][2]!="WORD")
			{	
				opcode=opp_table.fetch(the_list[i][2]);
				if(the_list[i][2]=="LDB")
					base_addr=sym_table.symtab[the_list[i][3]];
				if(opp_table.get_addr_mode(the_list[i][2])==1)
					objcode=opcode;
				else if(opp_table.get_addr_mode(the_list[i][2])==2){
					objcode=opcode;
					string r1,r2;
					get_reg(the_list[i][3],r1,r2);
					if(!r1.empty())	
						objcode+=map_reg(r1);
					if(!r2.empty())	
						objcode+=map_reg(r2);			
					else objcode+='0';
				}
				
				else if(ins_format==4){
					objcode+=concate_zero(dec_to_hex(hex_to_dec(opcode)+addr_mode),2);
					objcode+=flag_bit;
					string oper="";
					if(sym_table.symtab.count(the_list[i][3])) 
							oper=sym_table.symtab[the_list[i][3]];
					else if(lit_table.littab.count(the_list[i][3]))
							oper=lit_table.littab[the_list[i][3]];
					else 
							oper=concate_zero(the_list[i][3],3);
					if(addr_mode==1)
					{
						if(sym_table.symtab.count(the_list[i][3]) || lit_table.littab.count(the_list[i][3])){
							objcode+=concate_zero(oper,5);
						}
						else 
							objcode+=concate_zero(gen_data(the_list[i][3]),5);
					}
					else{
						objcode+=concate_zero(oper,5);
					}
				}
				else if(opp_table.get_addr_mode(the_list[i][2])==3){
					objcode+=concate_zero(dec_to_hex(hex_to_dec(opcode)+addr_mode),2);
					string oper="";	
					if(sym_table.symtab.count(the_list[i][3])) 
							oper=sym_table.symtab[the_list[i][3]];
					else if(lit_table.littab.count(the_list[i][3]))
							oper=lit_table.littab[the_list[i][3]];
					else {
							flag_bit='0';
					}
					if(flag_bit=='0')
					{
						objcode+=flag_bit;	
						objcode+=concate_zero(gen_data(the_list[i][3]),3);
					}
					else   {
						string pc=dec_to_hex(hex_to_dec(the_list[i][0])+3);
						string diff=hex_sub(oper,pc);
						if((str_to_dec(diff)>2047 || str_to_dec(diff)<(-2048)) && rel==false){
							diff=hex_sub(oper,base_addr);
							if(flag_bit=='A')
								flag_bit='C';
							else
								flag_bit='4';						
						}
						objcode+=flag_bit;
						objcode+=concate_zero(diff,3);
					}
				}
			}
			else{
				string temper=gen_data(the_list[i][3]);
				objcode+=temper;
			}
			if(ins_format==4){
				the_list[i][2]+='+';
			}
		
			the_list[i][4]=objcode;
		}
		catch(...){
			cout<<"block 2\n";
		}
	}
	
	for(int i=0;i<the_list.size();i++){
		the_list[i][0]=concate_zero(the_list[i][0],6);
	}	
}

vector<string> text_rec(int& i, string& size){
	vector<string> text;
	int n=10,ini=i;
	while(n--){
		text.push_back(the_list[i][4]);
		if(!text_break.empty())
		if(the_list[i][0]==text_break.front()){
			text_break.pop();
			i++;		
			break;
		}
		i++;
		if(i==the_list.size()){
			break;
		}
	}
	if(i==the_list.size()){
		size=hex_sub(prog_length,the_list[ini][0]);
	}
	else{
		size=hex_sub(the_list[i][0],the_list[ini][0]);
	}
	return text;	
}

void object_generator(){
	ofstream f;
	f.open("object_program.txt", ios::trunc | ios::out);
	f<<"H^"<<setw(6)<<left<<prog_name<<"^"<<start_addr<<"^"<<prog_length<<"\n";
	int t=the_list.size();
	string size="";
	vector<string> textr;
	int index=0,tem=0;
	while(t){
		string start=the_list[index][0];
		textr=text_rec(index,size);
		size=concate_zero(size,2);
		f<<"T^"<<start<<"^"<<size;
		for(int i=0;i<textr.size();i++){
			f<<"^"<<textr[i];
		}
			
		f<<"\n";
		t-=index-tem;
		tem=index;
	}
	for(int i=0;i<modi_rec.size();i++)
	{
		f<<"M^"<<concate_zero(modi_rec[i],6)<<"^05\n";
	}
	f<<"E^000000";
	cout<<"\n:::::::::::::::::::::::::::::::::::::END:::::::::::::::::::::::::::::::::::::::\n";
	f.close();
	
}

int main()
{
	FILE *fp=fopen("fibo.txt","r");
	pass1(fp);
	sym_table.show_sym();
	lit_table.show_lit();
	pass2();
	cout<<"\nIntermediate File\n";
	for(int i=0;i<the_list.size();i++){
		for(int j=0;j<5;j++){
			cout<<the_list[i][j]<<" ";
		}
		cout<<endl;
	}
	object_generator();
	return 0;
}


















