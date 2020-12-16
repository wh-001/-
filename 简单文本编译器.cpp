#include<iostream>
#include<string>
#include<cstdlib>
#include<ctype.h>
#include<cstdio>
#include<fstream>
using namespace std;
int NumberCount=0;//���ָ���
int CharCount=0;//��ĸ����
int PunctuationCount=0;//�����Ÿ���
int BlankCount=0;//�հ׷�����

class Node
{
public:
  string character;
  int cursor;
  int offset;
  Node* next;
  Node(){
    cursor=0;//ÿ�еĹ���ʼλ��
    offset=0;//ÿ�еĳ�ʼƫ��λ��
    next=NULL;
  }
};

class TextEditor
{
private:
  Node* head;
  string name;
  int line;//�ɸ��ĵ�����
  int length;//����
public:
  TextEditor();
  ~TextEditor();
  string GetName();
  void SetName(string name);
  int GetCursor();
  int MoveCursor(int offset);
  int SetCursor(int line,int offset);
  void AddText(const string s);
  void InsertText(int seat,string s);
  int FindText(string s);
  void DeleteText(string s);
  int GetLine();
  void Count();
  friend ostream& operator<<(ostream& out,TextEditor &text);
  Node* Gethead(){
    return head;
  }
  //int GetLength()
  //{
  //   return length;
  // }
 // int FindText(string s);
 // void DeleteText(int seat,string s);
};

TextEditor::TextEditor()
{
  head=NULL;
  name="test";//�ļ���ʼ��
  //tail=NULL;
  line=1;
  length=0;
}

TextEditor::~TextEditor()
{
  Node* p=head;
  Node* q;
  while(p!=NULL){
    q=p->next;
    delete p;
    p=q;
  }

}

int TextEditor::GetLine()
{
  return line;
}

string TextEditor::GetName()
{
  return name;
}

void TextEditor::SetName(string name)
{
  this->name=name;
}

int TextEditor::GetCursor()
{
  Node *p=head;
  while(p->next!=NULL)
    p=p->next;
  return p->cursor;
}

int TextEditor::MoveCursor(int offset)
{
  Node *p=head;
  int i=1;
  if(length+1<line){
    cout<<"�������!"<<endl;
    exit(0);
  }
  else{
    while(p->next!=NULL&&i<line){
      p=p->next;
      i++;
    }
  }
  if(offset>p->character.length()){
    cout<<"�ƶ�λ��̫��!"<<endl;
    exit(0);
  }
  else
    p->cursor+=offset;
  //cout<<"p ->cursor="<<p->cursor<<endl;
  return p->cursor;
}

int TextEditor::SetCursor(int line,int offset)
{
  this->line=line;
  //cout<<"line="<<this->line<<endl;
  return MoveCursor(offset);
}

void TextEditor::AddText(const string s)
{
  line=length+1;
  Node* p=new Node;
  Node* q=head;
  p->character=s;
  p->next=NULL;
  if(head==NULL)
    head=p;
  else{
    while(q->next!=NULL)
      q=q->next;
    q->next=p;
  }

    length++;
    // line++;
}

void TextEditor::InsertText(int seat,string s)
{
  Node *p=head;
  int i=1;
  if(length+1<line){
    cout<<"�������!"<<endl;
    exit(0);
  }
  else{
    while(p->next!=NULL&&i<line){
      p=p->next;
      i++;
    }
  }
  //MoveCursor(seat);
  //cout<<"p->cursor="<<p->cursor<<endl;
  string substr;
  for(int i=seat;i<s.length()+seat&&i<=p->character.length();i++)
  substr+=p->character[i];

  p->character.insert(p->cursor,s);


  cout<<"substr="<<substr<<endl;
  DeleteText(substr);//�����Ӵ�
  p->cursor=0;//�������
}

ostream& operator<<(ostream& out,TextEditor &text)
{
  int i=1;
  Node* p=text.Gethead();
  while(p!=NULL){
    out<<p->character<<endl;
    p=p->next;
  }
  // cout<<"length="<<text.GetLength()<<endl;
  return out;
}

int TextEditor::FindText(string P)
{
  Node* q=head;
  //int templine=1;
  line=1;
  int p=0;
  int t=0;
  int plen=P.length()-1;
  //cout<<"P="<<P<<endl;
  //cout<<"plen="<<plen<<endl;
  int tlen=q->character.length();
  while(q!=NULL){
      p=0;
      t=0;
    tlen=q->character.length();
    if(tlen<plen){
      line++;
       q=q->next;
    }

    while(p<plen&&t<tlen){
      if(q->character[t]==P[p]){
        t++;
        p++;
      }
      else{
        t=t-p+1;
        p=0;
      }
    }
   // cout<<"P="<<P<<endl;
   // cout<<"p="<<p<<endl;
   // cout<<"plen="<<plen<<endl;
    if(p>=plen){

      return t-plen+1;
    }


    else{
      line++;
      q=q->next;
    }

  }
  return -1;
}

void TextEditor::DeleteText(string s)
{
  Node *p=head;
  int i=1;
  int k=FindText(s);
  if(k==-1)
    cout<<"δ���ָ��ַ���!"<<endl;
  else{
    while(p!=NULL&&i<line){
      p=p->next;
      // cout<<p->character<<endl;
      i++;
    }

    p->character.erase(k-1,s.length());
    cout<<"ɾ���ɹ���"<<endl;
  }
}

void TextEditor::Count()
{
  Node *p=head;
  NumberCount=0;
  CharCount=0;
  PunctuationCount=0;
  BlankCount=0;
  while(p!=NULL){
      for(int i=0;i<p->character.length();i++){
        if(p->character[i]>='0'&&p->character[i]<='9')
          NumberCount++;
        else if(p->character[i]>'a'&&p->character[i]<'z'||p->character[i]>'A'&&p->character[i]<'Z')
          CharCount++;
        else if(ispunct(p->character[i]))
          PunctuationCount++;
        else if(p->character[i]==' ')
          BlankCount++;
      }
      p=p->next;
  }
}

int main()
{
  int i,j,k,n=2;
  string s,t,name;
  TextEditor text;
  cout<<"---------------------------------------"<<endl;
  cout<<"1.����ַ�"<<endl;
  cout<<"2.�����ĵ�����"<<endl;
  cout<<"3.��ȡ�ĵ�����"<<endl;
  cout<<"4.��ʾ���λ��"<<endl;
  cout<<"5.���ù��λ�ã��ڹ��λ�ô������ı�"<<endl;
  cout<<"6.���ĵ��в����ı�"<<endl;
  cout<<"7.���ĵ���ɾ���ı�"<<endl;
  cout<<"8.ͳ����ĸ�����֡������š��հ׷��ż����ַ�����"<<endl;
  cout<<"9.�����ı�"<<endl;
  cout<<"0.�˳�"<<endl;
  while(n){
    // cout<<endl;
    cout<<endl;
    cout<<"---------------------------------------"<<endl;
    cout<<"������:";
    cin>>n;
    getchar();
    switch(n){
      case 1: cout<<"�������ַ�:"; getline(cin,s,'\n'); text.AddText(s); break;
      case 2: cout<<"�������ĵ�����:"; cin>>name; text.SetName(name); break;
      case 3: cout<<text.GetName()<<endl; break;
      case 4: cout<<"����ڵ�"<<text.GetLine()<<"�У���"<<text.GetCursor()<<"���ַ�ǰ!"<<endl; break;
      case 5:{
        cout<<"��������:";
        cin>>i;
        cout<<"����ڵ�"<<text.GetCursor()<<"���ַ�ǰ!"<<endl;
        cout<<"�����ƶ�λ��:";
        cin>>j;
        cout<<"��������ַ�:";
        getchar();
        getline(cin,s);
        text.InsertText(text.SetCursor(i,j),s); break;
      }
      case 6: {
        cout<<"������ҵ��ַ���:";
        getline(cin,s);
        int k=text.FindText(s);
        if(k==-1)
          cout<<"����ʧ��!"<<endl;
        else
          cout<<"�������ı��״γ�����:"<<text.GetLine()<<"�У���"<<k<<"���ַ���!"<<endl;
          break;
      }
      case 7: cout<<"����Ҫɾ�����ַ���:"; getline(cin,s); text.DeleteText(s); break;
      case 8: {
        text.Count();
        cout<<"�ĵ��й���:"<<endl;
        cout<<NumberCount<<"������"<<endl;
        cout<<CharCount<<"����ĸ"<<endl;
        cout<<PunctuationCount<<"��������"<<endl;
        cout<<BlankCount<<"���հ��ַ�"<<endl;
        cout<<"����"<<NumberCount+CharCount+PunctuationCount+BlankCount<<"���ַ�!"<<endl;
        break;
      }
      case 9: cout<<text; break;
      case 0:{
        string ss=text.GetName();
        ss+=".txt";
        cout<<ss<<endl;
        ofstream outFile(ss.c_str());
        Node* p=text.Gethead();
        while(p!=NULL){
          outFile<<p->character<<endl;
          p=p->next;
        }
        exit(0);
        break;
      }
      default: cout<<"����������������룡"<<endl; break;
    }

  }
}