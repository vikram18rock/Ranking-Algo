#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <math.h>
using namespace std;
#define k 40
class team
{
    private:
        string team_name;
        float team_rating;
    public:
        void set_rating(float rating);
        float get_rating();
        float expectation(team x);
};
void team::set_rating(float rating)
{
    team_rating=rating;
    return;
}
float team::get_rating()
{
    return team_rating;
}
float team::expectation(team x)
{
    float rating1=team_rating;
    float rating2=x.get_rating();
    float value=pow(10,((rating1-rating2)/400));
    return 1/(1+value);
}
int main()
{
    unordered_map<string,int> m;
    m.insert(make_pair("Hyderabad",0));
    m.insert(make_pair("Indians",1));
    m.insert(make_pair("Lions",2));
    m.insert(make_pair("Pune",3));
    m.insert(make_pair("Challengers",4));
    m.insert(make_pair("Knight",5));
    m.insert(make_pair("Daredevils",6));
    m.insert(make_pair("XI",7));
    m.insert(make_pair("Super",8));
    m.insert(make_pair("Royals",9));
    m.insert(make_pair("Charges",10));
    m.insert(make_pair("Tuskers",11));
    m.insert(make_pair("Warriors",12));
    team object[13];
    for(int i=0;i<13;i++)
    {
        object[i].set_rating(500);
    }
    fstream fin;
    fin.open("./matches.csv", ios::in);
    vector<string> row;
    string line, word, temp;
    while (fin >> temp) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        if(row.size()>1)
        {
            string name1=row[0];
            string name2=row[1];
            string name3=row[6];
            float result;
            for(int i=0;i<name1.size();i++)
            {
                if(name1[i]==' ')
                {
                    string temp="";
                    i++;
                    while(name1[i]!=' '&&i<name1.size())
                    {
                        temp+=name1[i];
                        i++;
                    }
                    name1=temp;
                    break;
                }
            }
            for(int i=0;i<name2.size();i++)
            {
                if(name2[i]==' ')
                {
                    string temp="";
                    i++;
                    while(name2[i]!=' '&&i<name2.size())
                    {
                        temp+=name2[i];
                        i++;
                    }
                    name2=temp;
                    break;
                }
            }
            for(int i=0;i<name3.size();i++)
            {
                if(name3[i]==' ')
                {
                    string temp="";
                    i++;
                    while(name3[i]!=' '&&i<name3.size())
                    {
                        temp+=name3[i];
                        i++;
                    }
                    name3=temp;
                    break;
                }
            }
            cout<<name1<<"***"<<name2<<"***"<<name3<<"\n";
            if(name1==name3)
                result=1;
            else if(name2==name3)
                result=0;
            else
                result=0.5;
            if(m.find(name1)==m.end()||m.find(name2)==m.end())
                continue;
            int value1=m[name1];
            int value2=m[name2];
            float expectationA=object[value1].expectation(object[value2]);
            float expectationB=1-expectationA;
            float oldratingA=object[value1].get_rating();
            float oldratingB=object[value2].get_rating();
            float newratingA=oldratingA+k*(result-expectationA);
            float newratingB=oldratingB+k*(result-expectationB);
            object[value1].set_rating(newratingA);
            object[value2].set_rating(newratingB);
        }
    }
    for(int i=0;i<13;i++)
        cout<<object[i].get_rating()<<"\n";
    return 0;
}
