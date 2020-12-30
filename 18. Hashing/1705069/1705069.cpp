#include<iostream>
#include<string>
#include<list>
#include<climits>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<random>

using namespace std;
#define ll long long
#define INF LLONG_MIN

vector<string> words, searchable;

void sieve(ll lim, bool *prime) { 
        // memset(prime, true, sizeof(prime));
        
        for (ll p = 2; p * p <= lim; p++) { 
            if (prime[p] == true) { 
                for (ll i = p * p; i <= lim; i += p) 
                    prime[i] = false; 
            } 
        } 
}

ll getPrime(ll n, ll lim, bool *prime) { 
        ll k = 1;
        ll res = -1; 
        for (ll i = n + 1; i < lim; i++) { 
        if (prime[i] == true) 
            k--;  
        if (k == 0) { 
            res = i; 
            break; 
        } 
        } 
        return res; 
}  


class hashTable{
    
    list<pair<string, ll>> *table;
    ll m, col, probe;
    ll hashChoice, method;
    

public:
    
    hashTable (ll size, ll h, ll meth){
        m = size;
        table = new list<pair<string, ll>>[m];
        col = 0;
        probe = 0;
        hashChoice = h;
        method = meth;
    }

    ll hash (string s){
        ll hash_value = 0;

        if (hashChoice == 1){
            ll p_pow = 1, p = 97;
            for (char c : s){
                hash_value = ((hash_value) + c*p_pow) % m;
                p_pow = (p_pow*p) % m;
            }
        
        } else {
            hash_value = 5381;
            for (char c : s){
                hash_value = (hash_value*33 + c) % m;
            }
        }
        
        return hash_value;
    }

    ll auxHash (string s){
        ll p = 269, hash_value = 0, p_pow = 1;

        for (char c : s){
            hash_value = ((hash_value) + c* p_pow) % m;
            p_pow = (p_pow*p) % m;
        }

        return hash_value;
    }

    ll doubleHash (string s, ll i){
        return (hash(s) + i * auxHash(s)) % m;
    }

    ll customHash (string s, ll i){
        return (hash(s) + 69 *i*auxHash(s) + 269*i*i) % m;
    }

    void insert (string k, ll v){
       
        if (method == 1){
             //Chaining
            ll h = hash(k);
            if (!table[h].empty()){
            col++;
            bool found = false;
            for(auto itr = table[h].begin(); itr != table[h].end(); ++itr){
                if (itr->first == k){
                    itr->second = v;
                    found = true;
                    break;
                }
            }
            if (!found) table[h].push_back({k, v});
            } else {
                table[h].push_back({k, v});
            }
        } else {
            //Double hash or CustomHash
            for(ll i = 0; i < m; ++i){
                ll h = method == 2 ? doubleHash(k, i) : customHash(k, i);
                if (table[h].empty()){
                    table[h].push_back({k, v});
                    break;
                }
                col++;
            }
        }
        
        
    }

    ll search (string k){
        
        if (method == 1){
            //chaining
            ll h = hash(k);
            for(auto itr = table[h].begin(); itr != table[h].end(); ++itr){
                probe++;
                if (itr->first == k){
                    return itr->second;
                }
            }
        } else{
            //Double hash or Custom Hash
            for(ll i = 0; i < m; ++i){
                ll h = method == 2 ? doubleHash(k, i) : customHash(k, i);
                probe++;
                if (table[h].front().first == k){
                    return table[h].front().second;
                }
            }
        }


        return INF;
    }

    void delete_ (string k){
        if (method == 1){
            //chaining
            ll h = hash(k);
            for(auto itr = table[h].begin(); itr != table[h].end(); ++itr){
                if (itr->first == k){
                    table[h].erase(itr);
                }
            }
        } else{
            //Double hash or Custom Hash
            for(ll i = 0; i < m; ++i){
                ll h = method == 2 ? doubleHash(k, i) : customHash(k, i);
                if (table[h].front().first == k){
                    table[h].clear();
                }
            }
        }
    }

    void generate () {
        char alphanum[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"};

        if (method == 1){
            cout<<"--Chaining Method--\n";
        } else if (method == 2){
            cout<<"--Double Hashing--\n";
        } else if (method == 3){
            cout<<"--Custom Probing--\n";
        }

        

        if (words.empty()){
            for(ll i = 0; i < m; ++i){
                string s;
                for(ll j = 0; j < 7; ++j){
                    s += alphanum[rand() % 52]; 
                }
                words.push_back(s);
            }
        }
        
        if (searchable.empty()){
            for (ll i = 0; i < m/10; ++i){
                searchable.push_back(words[rand() % m]);
            }
        }
        
        

        for (ll i = 0; i < m; ++i){
            insert(words[i], i+1);
        }
        

        for(ll i = 0; i < m/10; ++i){
            ll v = search(searchable[i]);
            // cout<<s<<" "<<v<<" "<<pos+1<<endl;
        }
        cout<<"Collisions: "<<col<<endl;
        cout<<"Average Probes: "<<(probe*1.0/(m*1.0/10))<<endl;
    }

    
};



int main(){
    srand (time(NULL));
    ll m;
    cin>>m;

    bool prime[m*2];
    fill(prime, prime + m*2, true);
    sieve(2*m, prime); 
    m = getPrime(m, 2*m, prime);

    hashTable h(m, 1, 1);
    hashTable h1(m, 1, 2);
    hashTable h2(m, 1, 3);
    hashTable h3(m, 2, 1);
    hashTable h4(m, 2, 2);
    hashTable h5(m, 2, 3);

    cout<<"\nUsing 1st hash function\n";
    h.generate();
    h1.generate();
    h2.generate();
    cout<<"\nUsing 2nd hash function\n";
    h3.generate();
    h4.generate();
    h5.generate();
}