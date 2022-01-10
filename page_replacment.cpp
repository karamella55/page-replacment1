
#include <iostream>
#include <unordered_set>
#include <queue>
#include "page_replacment.h"
#include <unordered_map>
using namespace std;


int FIFO(int pages[], int numbers, int frame)
{
   //3shan nshof al data mtrtba wala la
    unordered_set<int> x;
    //bnsave al data bel fifo algo..
    queue<int> variables;

  //variable 3shan n3d al page faults..
    int PageFault = 0;
    for (int i = 0; i < numbers; i++)
    {
      //byshof al frames tst7ml arkam tanya wala la..
        if (x.size() < frame)
        {
           //law al shart aley fo2 mt72a2sh bnbtedy nd5l al arkam
            if (x.find(pages[i]) == x.end())
            {
                
                x.insert(pages[i]);

                PageFault++;

               //bnd5l al rakam fel queue
                variables.push(pages[i]);
            }
        }

        //law al frames atmalet fa hnbtedy nst5dm al fifo algo mn hena
        else
        {
            //check law arkm alrealdy m7toto fel frames wala la..
            if (x.find(pages[i]) == x.end())
            {
               //bnsave awl rakam 3shan nshelo
                int value = variables.front();

            //bnshel awl rkam
                variables.pop();

               
                x.erase(value);

               //bninsert al rakam al gded fel frame
                x.insert(pages[i]);

                //bnpush al rakam al gded fel queue
                variables.push(pages[i]);

               
                PageFault++;
            }
        }
    }

    return PageFault;
}






int LRU(int pages[], int numbers, int frames)
{
    //3shan nshof al data mtrtba wala la
    unordered_set<int> x;
    //3shan nstore al lru index
    unordered_map<int, int> indx;

    
    int PageFault = 0;
    for (int i = 0; i < numbers; i++)
    {
      //bnshof al frames yst7ml arkam tany wala la..
        if (x.size() < frames)
        {
            //bnbtedy nd5l al arkam we check aza kat mawgoda abl kda wala la..
            if (x.find(pages[i]) == x.end())
            {
                x.insert(pages[i]);
                PageFault++;
            }

            //bnstore al recently used index bt3t koll rakam
            indx[pages[i]] = i;
        }

        //lama al frames bttmely bnbtedy nst5dm al LRU
        else
        {
           //bntcheck aza kan al rakam mawgod wwala la..
            if (x.find(pages[i]) == x.end())
            {
               //bndwr 3ala al least recently used fel set
                int Least_Recently_used = INT_MAX, val;
                for (auto i = x.begin(); i != x.end(); i++)
                {
                    if (indx[*i] < Least_Recently_used)
                    {
                        Least_Recently_used = indx[*i];
                        val = *i;
                    }
                }

               //bnremove el index
                x.erase(val);
                //bn7ot al rakam al gded
                x.insert(pages[i]);

                PageFault++;
            }
            //bnstore al recently used index bt3t koll rakam
            indx[pages[i]] = i;
        }
    }

    return PageFault;
}

bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function aley btdwar 3al data aley masto5dmtsh b2alha kterr
// fe al most2bl[0..pn-1]
int predict(int pg[], vector<int>& fr, int pn, int index)
{
    // Store el index bta3 al pages aley htost5dm  fel most2bal
    
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        
        // law al page msh mawgoda fel most2bal 3alem 3aleha
        if (j == pn)
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // law koll al pages msh mawgoda fel most2bal rag3 ay wahda menhom aw yrg3 0
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    //bncrate array fady.
    vector<int> fr;

    //bnmshy fell array we nbtedy n7seb al hit wel miss.
    int hit = 0;
    for (int i = 0; i < pn; i++) {

        //law al page la2aha fel frame (HIT)
        if (search(pg[i], fr)) {
            hit++;
            continue;
        }

        // law al page msh mawgoda  MISS

        // law feh ms7a fadya fell frames
        if (fr.size() < fn)
            fr.push_back(pg[i]);

        // bybtedy ydwr 3al page aley hyt3mlha replace
        else {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }
    cout << "HITS = " << hit << endl;
    cout << "MISS = " << pn - hit << endl;
}


int main()
{
    
    int n;
    cout << "welcome to my page replacment program" << endl;
    cout << "please enter the number of pages" << endl;
    cin >> n;
    int* p;
    p = new int[n];
    cout << "please enter the data of the "<< n<<" pages" << endl;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }


    /*int page[13];
    cout << "please enter the 13 numbers you want to add" << endl;
    for (int i = 0; i < 13; i++) {
        cin >> page[i];
    }*/
    cout <<"these are the elements you want  to add??"<<endl;
    for (int i = 0; i < n; i++)
        cout << p[i] << "  ";
    cout << endl;

    int numbers =n;
    int frames = 4;
    cout << "  " << endl;
    int chosse;
    cout << "please press (1) if you want FIFO algorithm or (2) to LRU algorithm or (3) to optimal algorith" << endl;
    cin >> chosse;

    switch (chosse) {

    case 1:
        cout << "you have chossed FIFO algorithm" << endl;
        cout << "the number of page faults is =" << endl;
        cout << FIFO(p, numbers, frames);
        break;



    case 2: 
        cout << "you have chossed LRU algorithm" << endl;
        cout << "the number of page faults is =" << endl;
        cout << LRU(p, numbers, frames);
        break;

    case 3:
        cout << "you have chossed optimal algorithm" << endl;
        optimalPage(p, numbers, frames);
        break;

    }

}


