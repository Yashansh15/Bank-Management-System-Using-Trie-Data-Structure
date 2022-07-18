#include<iostream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include<vector>
#include <iomanip>
using namespace std;
    MYSQL*conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    void acees_record();
    void dis_record();
    void sort_record();
    void full_txt_srch();
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 void exitt()
 {
    exit(0);
 }
 void retrurn()
 {
    char b;
    cout<<endl<<endl<<"\t\t\t\t\t\t"<<"Press Any Key To Return To Home Page :- "<< endl<<"  \t\t\t\t\t\t ";
    cin>>b;
 }
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& INSERT IN DATA &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 void insert_in_db(MYSQL*conn1)
 {
    stringstream ss;
    string name,city,card_type;
    int card_number,id;
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter Name: "<< endl<<"  \t\t\t\t\t\t";
    cin>>name;
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter Card_Number: "<< endl<<"  \t\t\t\t\t\t";
    cin>>card_number;
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter Card_Type: "<< endl<<"  \t\t\t\t\t\t";
    cin>>card_type;
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter City: "<< endl<<"  \t\t\t\t\t\t";
    cin>>city;
       ss<<"INSERT INTO test(name,card_number,card_type,city) VALUES ('" << name << "'," << card_number << ",'" << card_type <<"','"<<city<<"')";
    string query=ss.str();
    const char* q=query.c_str();
    int qstate=mysql_query(conn1,q);
    if(qstate==0){
        cout<<endl<<"  \t\t\t\t\t\t"<<"Record Inserted"<<endl;
    }
    else{
        cout<<endl<<"  \t\t\t\t\t\t"<<"Failed To Insert Record !!!"<<endl;
    }
 }
//*************************  __ UPDATE  __ *******************************************
 void update_data()
 {

    int qstate = 0;
    string name,city;
    int p;
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter Name To Update Details : "<< endl<<"\t\t\t\t\t\t";
    cin >> name;
    cout<<endl<<"  \t\t\t\t\t\t"<<"Choose The Field To Update : "<< endl<<"\t\t\t\t\t\t ";
    int op;
    stringstream ss;
    cout<<endl<<"  \t\t\t\t\t\t"<<"1 : CARD NUMBER "<< endl<<"\t\t\t\t\t\t ";
    cout<<endl<<"  \t\t\t\t\t\t"<<"2 : CARD TYPE"<< endl<<"\t\t\t\t\t\t ";
    cout<<endl<<"  \t\t\t\t\t\t"<<"3 : CITY"<< endl<<endl<<"\t\t\t\t\t\t";
    cout<<endl<<"  ---------------------------------------------------------------------------------------------------------------"<<endl<<endl<<"\t\t\t\t\t\t";
    cin>>op;
    cout<<endl<<"  ---------------------------------------------------------------------------------------------------------------"<<endl<<endl<<"\t\t\t\t\t\t";
    if(op==1)
    {
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter The New CARD NUMBER : "<<endl<<"\t\t\t\t\t\t";
    cin>>p;
    ss << "UPDATE test SET card_number =" << p << " WHERE name = '" << name << "'";

    }
    else if(op==2)
    {
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter The New Card TYPE : "<<endl<<"\t\t\t\t\t\t";
    cin>>city;
    ss << "UPDATE test SET card_type ='" << city << "' WHERE name = '" << name << "'";
    }
    else if(op==3)
    {
    cout<<endl<<"  \t\t\t\t\t\t"<<"Enter The New City  : "<<endl<<"\t\t\t\t\t\t";
    cin>>city;
    ss << "UPDATE test SET city ='" << city << "' WHERE name = '" << name << "'";
    }
    else
    {
    cout<<endl<<"  \t\t\t\t\t\t"<<endl<<" WRONG CHOICE !!!"<<endl;
    system("cls");
    update_data();

    }
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0)
    {
    cout << "Record Updated..." <<endl;
    }
    else
    {
    cout << "Insert Error !!" <<endl;
    }
 }
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 struct TriNode
 {
      TriNode*chara[256];
      bool we;
 };
 TriNode *createNode()
  {
      TriNode *pnode=new TriNode;
      pnode->we=false;
      for(int i=0;i<256;i++)
      {
         pnode->chara[i]=NULL;
      }
      return pnode;
  }
 TriNode*root=createNode();
 void insertData(TriNode *root,string data)
 {
      TriNode*start=root;
      for(int i=0;i<data.length();i++)
      {
         int indx=data[i]-'A';
         if(start->chara[indx]==NULL)
         {
             start->chara[indx]=createNode();
         }
         start=start->chara[indx];
      }
      start->we=true;
 }
//***************************************************************88
 void display_all_record_in_db(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1,vector<string>&data)
 {
      if(conn1)
      {
         int qstate=mysql_query(conn1,"SELECT id,name FROM test");
         if(!qstate)
         {
             res1=mysql_store_result(conn1);
             while(row1=mysql_fetch_row(res1))
             {
                 data.push_back(row1[1]);
             }
         }
      }
 }
//****************************************************************8
 void displaytrie(TriNode*root,char s[],int level)
 {
    if(root->we==true)
    {
        s[level]='\0';
        cout<<"\t\t\t\t\t\t"<<s<<endl;
        return;
    }
    int i;
    for(i=0;i<256;i++)
    {
        if(root->chara[i]!=NULL)
        {
            s[level]=i+'A';
            displaytrie(root->chara[i],s,level+1);
        }
    }
 }
//********************************************************************88
 bool isEmpty(TriNode* root)
 {
    for (int i = 0; i <256; i++)
        if (root->chara[i])
            return false;
    return true;
 }
 TriNode* delete_from_tri(TriNode* root, string key, int depth)
 {
    if (!root)
        return NULL;
    if (depth == key.size())
    {
        if (root->we)
            root->we= false;

        if (isEmpty(root))
        {
            delete (root);
            root = NULL;
        }
        return root;
    }
    int index = key[depth] - 'A';
    root->chara[index] =delete_from_tri(root->chara[index], key, depth + 1);
    if (isEmpty(root) && root->we == false)
    {
        delete (root);
        root = NULL;
    }
    return root;
 }
//********************************************************************************************8888
 void display_tri_by_req(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1,vector<string>&data,string req)
 {
  if(conn1)
    {
        int qstate=mysql_query(conn1,"SELECT * FROM test");
        if(!qstate){
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                 if(req=="name")
                 {
                 data.push_back(row1[1]);
                 }
                 else if(req=="card_type")
                 {
                    data.push_back(row1[3]);
                 }
                 else if(req=="city")
                 {
                    data.push_back(row1[4]);
                 }
            }
        }
   }
 }
 void display_as_per_req(string req)
 {
     TriNode*root1=createNode();
     vector<string>v1;
     display_tri_by_req(conn,row,res,v1,req);
     if(v1.empty())
     {
        cout<<"\t\t\t\t"<<" No Such Field Exist !!\n";
     }
     else
     {
     for(int i=0;i<v1.size();i++)
     {
        insertData(root1,v1[i]);
     }
     char s1[200];
     displaytrie(root1,s1,0);
     }
 }
//*****************************************************************************************************
 bool search(TriNode*root,string word)
 {
     TriNode*jokey=root;
     int f=0;
     for(int i=0;i<word.length();i++)
     {
         if(jokey->chara[word[i]-'A']==NULL)
         {
            f=1;
            break;
         }

         jokey=jokey->chara[word[i]-'A'];
     }
     if(f==1)return false;
     else return true;
 }
//************************************************************************************************************
 void print_record_as_per_req(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES *res1,string req)
 {
     int cnt=0;
     int f=0;
     TriNode*root1=createNode();
     string name,card_type,city,card_number;
    if(req=="name")
    {
       f=1;
       cout<<" \t\t\t\t\t\t Enter The CARD HOLDER NAME You Want TO Search : "<<endl<<"   \t\t\t\t\t\t ";
       cin>>name;
    }
    else if(req=="card_type")
    {
        f=2;
        cout<<" \t\t\t\t\t\t Enter The CARD TYPE You Want TO Search : "<<endl<<"   \t\t\t\t\t\t ";
        cin>>card_type;
    }
    else if(req=="city")
    {
        f=3;
        cout<<" \t\t\t\t\t\t Enter The CITY You Want TO Search : "<<endl<<"   \t\t\t\t\t\t ";
        cin>>city;
    }
    else if(req=="card_number")
    {
        f=4;
        cout<<" \t\t\t\t\t\t Enter The Card_Number Whose Record You Want \n   \t\t\t\t\t\t ";
        cin>>card_number;
    }
    if(f!=0 && f!=4)
    {
        vector<string>v1;
        display_tri_by_req(conn,row,res,v1,req);
        if(v1.empty())
        {
           cout<<endl<<"\t\t\t\t"<<" No Such Field Exist!!\n";
        }
        else
        {
           for(int i=0;i<v1.size();i++)
           {
               insertData(root1,v1[i]);
           }
        }
    }
     if(conn1)
     {
        int qstate=mysql_query(conn1,"SELECT * FROM test");
        if(!qstate)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                if(f==1 && name==row1[1] && search(root1,name))
                {
                     cnt++;
                     if(cnt==1)
                     {
                        cout<<endl<<"\t\t\t\t\t\t"<<"Found\n";
                        cout<<endl<<endl<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                     }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
                }
                else if(f==2 && card_type==row1[3] && search(root1,card_type))
                {
                     cnt++;
                     if(cnt==1)
                     {
                        cout<<endl<<endl<<"\t\t\t\t\t\t"<<"Found\n";
                        cout<<endl<<endl<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                     }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
                }
                else if(f==3 && city==row1[4] && search(root1,city))
                {
                     cnt++;
                     if(cnt==1)
                     {
                        cout<<endl<<"\t\t\t\t\t\t"<<"Found\n";
                        cout<<endl<<endl<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                     }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
                }
                else if(f==4 && card_number==row1[2])
                {
                     cnt++;
                     if(cnt==1)
                     {
                        cout<<endl<<"\t\t\t\t\t\t"<<"Found\n";
                        cout<<endl<<endl<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                     }
                       cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
                }
            }
        }
    }
    if(cnt==0)
    cout<<endl<<endl<<"\t\t\t\t"<<" NO SUCH RECORD FOUND !!\n";
 }
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7
 void display_of_db (MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res)
 {
     if(conn1)
     {
        int qstate = mysql_query(conn1, "SELECT * FROM test");
        if(!qstate)
        {
             res= mysql_store_result(conn1);
             cout<<endl<<endl<<endl<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
             while(row1 = mysql_fetch_row(res))
             {
             cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
             }
        }
     }
 }
 //^^^^^^^^^^^^^^^^^^^^^^^^^^ DELETE FORM DATABASE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^6
 void delete_from_db(MYSQL*conn1,string name)
 {
   int qstate =0;
   stringstream ss;
   //ss<<"DELETE FROM test ";
   ss<< " DELETE FROM test WHERE name='" << name << "'";
   string query = ss.str();
   const char* q = query.c_str();
   qstate = mysql_query(conn1,q);
   if(qstate==0)
   {
     cout<<left<<setw(20)<<"RECORD DELETED ... "<<endl;
   }
   else
   {
     cout<<left<<setw(20)<<"FAILED !!!"<<endl;
   }
 }
 //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 void full_txt_print_record(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1,string name)
 {
     int cnt=0;
     if(conn1)
     {
        int qstate=mysql_query(conn1,"SELECT * FROM test");
        if(!qstate)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                 if(name==row1[1] && search(root,name))
                 {
                     cnt++;
                     if(cnt==1)
                     {
                        cout<<endl<<endl<<"\t\t\t\t\t\t"<<"Found\n"<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                     }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
                 }
            }
        }
     }
     if(cnt==0)
     cout<<endl<<"\t\t\t\t\t\t"<<" No Such Record Found !! \n"<<endl;
 }
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7
 void sort_by_city(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1)
 {
    if(conn1)
    {
        int cnt=0;
        int qstate=mysql_query(conn1,"SELECT * FROM test ORDER BY city");
        if(!qstate)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                cnt++;
                if(cnt==1)
                {
                        cout<<endl<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
            }
        }
    }
 }
 void sort_by_card_name(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1)
 {
    if(conn1)
    {
        int cnt=0;
        int qstate=mysql_query(conn1,"SELECT * FROM test ORDER BY card_type");
        if(!qstate)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                cnt++;
                if(cnt==1)
                {
                        cout<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
            }
        }
     }
 }
 void sort_by_name(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES*res1)
 {
   if(conn1)
   {
        int cnt=0;
        int qstate=mysql_query(conn1,"SELECT * FROM test ORDER BY name");
        if(!qstate)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                cnt++;
                if(cnt==1)
                {
                        cout<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
            }
        }
    }
 }
//******************************************************************************************************************
 void print_record(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1,string name)
 {
     int cnt=0;
     if(conn1)
     {
        int qstate=mysql_query(conn1,"SELECT * FROM test");
        if(!qstate)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                if(name==row1[1])
                {
                         cnt++;
                         if(cnt==1)
                         {
                           cout<<endl<<endl;
                           cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                         }
                           cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row1[0]<<left<<setw(20)<<row1[1]<<left<<setw(20)<<row1[2]<<left<<setw(20)<<row1[3]<<left<<setw(20)<<row1[4]<<endl;
                }
            }
        }
     }
 }
 bool isLastNode(TriNode* root1)
 {
    for (int i = 0; i < 256; i++)
        if (root1->chara[i])
            return 0;
    return 1;
 }
 void suggestionsRec(TriNode* root1, string prefix,vector<string>&store)
 {
    if (root1->we)
    {
        store.push_back(prefix);
    }
    if (isLastNode(root1))
        return;

    for (int i = 0; i < 256; i++)
    {
        if (root1->chara[i])
        {
            prefix.push_back('A' + i);
            suggestionsRec(root1->chara[i], prefix,store);
            prefix.pop_back();
        }
    }
 }
 int printAutoSuggestions(TriNode* root1,string query,vector<string>&store)
 {
    TriNode* pCrawl = root1;
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index =query[level]-'A';
        if (!pCrawl->chara[index])
            return 0;
        pCrawl = pCrawl->chara[index];
    }
    bool isWord = (pCrawl->we == true);
    bool isLast = isLastNode(pCrawl);
    if (isWord && isLast)
    {
        print_record(conn,row,res,query);
        return -1;
    }
    if (!isLast)
    {
        string prefix = query;
        suggestionsRec(pCrawl, prefix,store);
        return 1;
    }
 }
//******
 void Ac_print_suggestions()
 {
     TriNode*root1=createNode();
     vector<string>v1,temp;
     display_tri_by_req(conn,row,res,v1,"name");
     for(int i=0;i<v1.size();i++)
     {
         insertData(root1,v1[i]);
     }
     string name;
     cout<<" \t\t\t\t\t\t Enter The Initials Of The Name You Want TO Search : "<<endl<<" \t\t\t\t\t\t   ";
     cin>>name;
     int comp = printAutoSuggestions(root1,name,temp);
     for(int i=0;i<temp.size();i++)
     {
         print_record(conn,row,res,temp[i]);
     }

     if (comp == 0)
     cout<<endl<<"\t\t\t\t\t\t"<<" No Such Record Found !!\n"<<endl;
 }
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7
 void sc_print_record(MYSQL*conn1,MYSQL_ROW row1,MYSQL_RES* res1,string name)
 {
     int cnt=0;
     if(conn1)
     {
         int qstate=mysql_query(conn1,"SELECT * FROM test");
         if(!qstate)
         {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                if(name==row1[1])
                {
                     cnt++;
                     cout<<endl<<"\t\t\t\t\t\t "<<" --> "<<left<<setw(10)<<row1[1]<<endl;
                }
            }
        }
     }
 }
 void sc_suggestionsRec(TriNode* root1, string prefix,vector<string>&store)
 {
    if (root1->we)
    {
        store.push_back(prefix);
    }
    if (isLastNode(root1))
        return;

    for (int i = 0; i < 256; i++)
    {
        if (root1->chara[i])
        {
            prefix.push_back('A' + i);
            sc_suggestionsRec(root1->chara[i], prefix,store);
            prefix.pop_back();
        }
    }
 }
 int sc_printAutoSuggestions(TriNode* root1,string query,vector<string>&store)
 {
    TriNode* pCrawl = root1;
    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index =query[level]-'A';
        if (!pCrawl->chara[index])
            return 0;
        pCrawl = pCrawl->chara[index];
    }
    bool isWord = (pCrawl->we == true);
    bool isLast = isLastNode(pCrawl);
    if (isWord && isLast)
    {
        sc_print_record(conn,row,res,query);
        return -1;
    }
    if (!isLast)
    {
        string prefix = query;
        //store.push_back(prefix);
        sc_suggestionsRec(pCrawl, prefix,store);
        return 1;
    }
 }//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 void spell_chk()
 {
     TriNode*root1=createNode();
     vector<string>v1,temp;
     display_tri_by_req(conn,row,res,v1,"name");
     for(int i=0;i<v1.size();i++)
     {
         insertData(root1,v1[i]);
     }
     string ppp;
     cout<<" \t\t\t\t\t\t Enter The Name You Want TO Search : "<<endl<<"  \t\t\t\t\t\t ";
     cin>>ppp;
     int cnt=0;
     if(conn)
     {
         int qstate=mysql_query(conn,"SELECT * FROM test");
         if(!qstate)
         {
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                if(ppp==row[1] && search(root,ppp))
                {
                     cnt++;
                     if(cnt==1)
                     {
                        cout<<endl<<endl<<"\t\t\t\t\t\t"<<" The Record With Same Spelling Found!! "<<endl<<endl;
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<"ID"<<left<<setw(20)<<"NAME"<<left<<setw(20)<<"CARD_NUMBER"<<left<<setw(20)<<"CARD_TYPE"<<left<<setw(20)<<"CITY"<<endl<<endl;
                     }
                        cout<<endl<<"\t\t\t\t"<<left<<setw(20)<<row[0]<<left<<setw(20)<<row[1]<<left<<setw(20)<<row[2]<<left<<setw(20)<<row[3]<<left<<setw(20)<<row[4]<<endl;
                }
            }
         }
     }
  if(cnt==0)
  {
            cout<<endl<<"  \t\t\t\t\t\t"<<" The Record With Same Spelling NOT FOUND  !!! "<<endl<<endl<<endl;
            cout<<"  \t\t\t\t\t\t"<<" Here Are Some Suggestion Related To Your Name : -"<<endl<<endl;
            int comp = sc_printAutoSuggestions(root1,ppp,temp);
            for(int i=0;i<temp.size();i++)
            {
               sc_print_record(conn,row,res,temp[i]);
            }
            if (comp == 0)
            cout<<endl<<"\t\t\t\t\t\t"<<" No Such Record Found !!\n"<<endl;
  }
 }
//************************************************************************************************************************************
//---------------------------------------- ACCESS RECORD -----------------------------------------------------------------------------
 void acees_record()
 {
    int choice;
    cout<<"\t\t\t\t\t\t ACCESS THE RECORDS "<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t\t\t Select The Operation You Want To Perform:- "<<endl<<endl;
    cout<<endl<<"\t\t\t\t\t\t 1.  Show All The Records "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 2.  Sort By The Requirements "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 3.  Full Text Search "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 4.  Display Distinct Record By Field"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 5.  Auto-Complete Operation "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 6.  Spell Checker Operation"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 7.  Exit "<<endl<<endl;
    cout<<"\t\t\t\t\t\t Enter Your Choice :- "<<endl<<"  \t\t\t\t\t\t ";
    cin>>choice;
    vector<string>v;
    display_all_record_in_db(conn,row,res,v);
    for(int i=0;i<v.size();i++)
    {
       insertData(root,v[i]);
    }
    switch(choice)
    {
        case 1:
        {
            system("cls");
            display_of_db(conn, row, res);
            retrurn();
            break;
        }
        case 2:
            system("cls");
            sort_record();
            break;
        case 3:
        {
            system("cls");
            full_txt_srch();
            break;
        }
        case 4:
            system("cls");
            dis_record();
            break;
        case 5:
            system("cls");
            Ac_print_suggestions();
            retrurn();
            break;
        case 6:
            system("cls");
            spell_chk();
            retrurn();
            break;
        case 7:
            system("cls");
            cout<<endl<<endl<<endl<<"\t\t\t\t\t\t  THANK - YOU  !!!"<<endl<<endl ;
            exitt();
            break;
        default:
            cout<<endl<<endl<<endl;
            cout<<"\t\t\t\t\t\t Wrong Choice Entered !!"<<endl<<endl;
            break;
        }
 }
//********************************************** FULL TEXT SEARCH ****************************************************************************
 void full_txt_srch()
 {
    int choice;
    cout<<"\t\t\t\t\t\t FULL TEXT SEARCH THE RECORD "<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t\t\t Select The Operation You Want To Perform :- "<<endl<<endl;
    cout<<endl<<"\t\t\t\t\t\t 1.  Search By Name "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 2.  Search By Card_Type "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 3.  Search By Card_Number"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 4.  Search By City"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 5.  Return To Previous Page"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 6.  Exit "<<endl<<endl;
    cout<<"\t\t\t\t\t\t  Enter Your Choice :- "<<endl<<"  \t\t\t\t\t\t ";
    cin>>choice;
      switch(choice)
      {
         case 1:
         {
             system("cls");
             string ppp="name";
             print_record_as_per_req(conn,row,res,ppp);
             retrurn();
             break;
         }
        case 2:
        {
             system("cls");
             string ppp="card_type";
             print_record_as_per_req(conn,row,res,ppp);
             retrurn();
             break;
        }
        case 3:
        {
             system("cls");
             string ppp="card_number";
             print_record_as_per_req(conn,row,res,ppp);
             retrurn();
             break;
        }
        case 4:
        {
             system("cls");
             string ppp="city";
             print_record_as_per_req(conn,row,res,ppp);
             retrurn();
             break;
        }
        case 5:
             system("cls");
             acees_record();
             break;
        case 6:
             system("cls");
             cout<<endl<<endl<<endl<<"\t\t\t\t\t\t  THANK - YOU  !!!" <<endl<<endl;
             exitt();
             break;
        default:
            cout<<endl<<endl<<endl;
            cout<<"\t\t\t\t\t\t Wrong Choice Entered !!"<<endl<<endl;
            break;
      }
 }


//********************************************* DISPLAY DISTINCT RECORD **************************************************************************8
 void dis_record()
 {
    int choice;
    cout<<"\t\t\t\t\t\t DISPLAY THE DISTINCT RECORD "<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t\t\t Select The Operation You Want To Perform :- "<<endl<<endl;
    cout<<endl<<"\t\t\t\t\t\t 1.  Display By Name "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 2.  Display By Card_Type "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 3.  Display By City"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 4.  Return To Previous Page"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 5.  Exit "<<endl<<endl;
    cout<<"\t\t\t\t\t\t  Enter Your Choice :- "<<endl<<"  \t\t\t\t\t\t ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
            system("cls");
            string par="name";
            display_as_per_req(par);
            retrurn();
            break;
        }
        case 2:
        {
            system("cls");
            string par="card_type";
            display_as_per_req(par);
            retrurn();
            break;
        }
        case 3:
        {
            system("cls");
            string par="city";
            display_as_per_req(par);
            retrurn();
            break;
        }
        case 4:
            system("cls");
            acees_record();
            break;
        case 5:
            system("cls");
            cout<<endl<<endl<<endl<<"\t\t\t\t\t\t  THANK - YOU  !!!" <<endl<<endl;
            exitt();
            break;
        default:
            cout<<endl<<endl<<endl;
            cout<<"\t\t\t\t\t\t Wrong Choice Entered !!"<<endl<<endl;
            break;
    }


 }
//****************************************** MANIPULATE THE RECORD****************************************************************
 void manipulate_record()
 {
    int choice;
    cout<<"\t\t\t\t\t\t MANIPULATE THE RECORDS "<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t\t\t Select The Operation You Want To Perform :- "<<endl<<endl;
    cout<<endl<<"\t\t\t\t\t\t 1.  Insert The Records "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 2.  Delete The Record "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 3.  Update The Record "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 4.  Exit "<<endl<<endl;
    cout<<"\t\t\t\t\t\t Enter Your Choice :- "<<endl<<"  \t\t\t\t\t\t ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
             system("cls");
             char pqr='Y';
             while(pqr=='Y')
             {
                 insert_in_db(conn);
                 cout<<endl<<endl<<"\t\t\t\t\t\tDo You Want To Enter More Data (Y/N):- "<<endl<<"  \t\t\t\t\t\t" ;
                 cin>>pqr;
                 system("cls");
             }
             vector<string>v;
             display_all_record_in_db(conn,row,res,v);
             for(int i=0;i<v.size();i++)
             {
                 insertData(root,v[i]);
             }
             retrurn();
             break;
        }
        case 2:
        {
             system("cls");
             string str;
             cout<<endl<<endl<<"\t\t\t\t\tEnter The Name You Want To Delete:- "<<endl<<"  \t\t\t\t\t\t";
             cin>>str;
             delete_from_tri(root,str,0);
             delete_from_db(conn,str);
             retrurn();
             break;
        }
        case 3:
             system("cls");
             update_data();
             system("cls");
             retrurn();
             break;
        case 4:
             system("cls");
             cout<<endl<<endl<<endl<<"\t\t\t\t\t\t  THANK - YOU  !!!" <<endl<<endl;
             exitt();
             break;
        default:
            cout<<endl<<endl<<endl;
            cout<<"\t\t\t\t\t\t Wrong Choice Entered !!"<<endl<<endl;
            break;
    }
 }
//*************************************** SORT RECORD ******************************************************88
 void sort_record()
 {
    int choice;
    cout<<"\t\t\t\t\t\t SORT THE RECORDS "<<endl<<endl<<endl<<endl;
    cout<<"\t\t\t\t\t\t Select The Operation You Want To Perform:- "<<endl<<endl;
    cout<<endl<<"\t\t\t\t\t\t 1.  Sort By Name "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 2.  Sort By CITY "<<endl<<endl;
    cout<< "\t\t\t\t\t\t 3.  Sort By CARD Type"<<endl<<endl;
    cout<<"\t\t\t\t\t\t 4.  Exit "<<endl<<endl;
    cout<<"\t\t\t\t\t\t 5.  Return To Previous Page "<<endl<<endl;
    cout<<"\t\t\t\t\t\t Enter Your Choice :- "<<endl<<"  \t\t\t\t\t\t ";
    cin>>choice;
    switch(choice)
    {
        case 1:
        {
             system("cls");
             sort_by_name(conn,row,res);
             retrurn();
             break;
        }
        case 2:
             system("cls");
             sort_by_city(conn,row,res);
             retrurn();
             break;
        case 3:
             system("cls");
             sort_by_card_name(conn,row,res);
             retrurn();
             break;
        case 4:
             system("cls");
             cout<<endl<<endl<<endl<<"\t\t\t\t\t\t  THANK - YOU  !!!"<<endl<<endl ;
             exitt();
             break;
        case 5:
             system("cls");
             acees_record();
             break;
        default:
             cout<<endl<<endl<<endl;
             cout<<"\t\t\t\t\t\t Wrong Choice Entered !!"<<endl<<endl;
             break;
    }
 }
//+++++++++++++++++++++++++++++++++++++++++++++++++  MAIN  FUNCTION  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 int main()
 {
      conn=mysql_init(0);
      conn=mysql_real_connect(conn,"192.168.43.126","yas","yas","youtube",0,NULL,0);
      int run=1;
      int ans;
      while(run==1)
      {
         system("cls");
         cout<<"\t\t\t\t\t\tWelcome to the Bank ATM Server operation"<<endl<<endl<<endl<<endl;
         cout<<"\t\t\t\t\t\tSelect the operation you want to perform:- "<<endl<<endl;
         cout<<endl<<"\t\t\t\t\t\t 1.  Access the Record "<<endl<<endl;
         cout<<"\t\t\t\t\t\t 2.  Manipulate the Record "<<endl<<endl;
         cout<<"\t\t\t\t\t\t 3.  Exit "<<endl<<endl;
         cout<<"\t\t\t\t\t\t Enter Your Choice :- "<<endl<<endl<<"  \t\t\t\t\t\t ";
         cin>>ans;
         switch(ans)
         {
            case 1:
                system("cls");
                acees_record();
                break;
            case 2:
                system("cls");
                manipulate_record();
                break;
            case 3:
                system("cls");
                cout<<endl<<endl<<endl<<"\t\t\t\t\t\t  THANK - YOU  !!!" <<endl<<endl;
                run=0;
                exitt();
                break;
            default:
                cout<<endl<<endl<<endl;
                cout<<"\t\t\t\t\t\t Wrong Choice Entered !!"<<endl<<endl;
                break;
        }
 }
        return 0;
 }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   THE  END  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// CREATED BY:- YASHANSH & PARAS ||
// SPECIAL THANKS :- PRIYANSH ||




