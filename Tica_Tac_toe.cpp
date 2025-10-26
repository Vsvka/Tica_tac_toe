
//libraries
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
using namespace std;


//board set up
void printBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << (board[i] == ' ' ? char('1' + i) : board[i]);
        if (i % 3 != 2) cout << " |";
        if (i % 3 == 2 && i != 8) cout << "\n-----------\n";
    }
    cout << "\n\n";
}


//function for checking winning condition
bool checkWin(const vector<char>& board, char player) {
    vector<vector<int>> wins = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (auto line : wins)
        if (board[line[0]]==player && board[line[1]]==player && board[line[2]]==player) return true;
    return false;
}


//checking if all spots are filled
bool boardCheck(const vector<char>& board) {
    for (char c : board) if (c == ' ') return false;
    return true;
}



//code from main got transfered here in order to play regular game
void play_regular() {
    vector<char> board(9, ' ');
    char current = 'X';
    cout << "Welcome to Tic-Tac-Toe\nPlayer 1: X, Player 2: O\n";
    while (true) {
        printBoard(board);
        int move;
        cout << "Player " << current << ", turn (1-9): ";
        if (!(cin >> move)) { 
            cout << "Invalid input. Try again please.\n"; 
            return; 
        }
        if (move < 1 || move > 9 || board[move - 1] != ' ') { 
            cout << "Invalid move. Try again please.\n"; 
            continue; 
        }
        board[move - 1] = current;
        if (checkWin(board, current)) { 
            printBoard(board); cout << current << " won\n"; 
            return; 
        }
        if (boardCheck(board)) { 
            printBoard(board); cout << "Tie\n"; 
            return; 
        }
        current = (current == 'X') ? 'O' : 'X';
    }
}




//checking for validness of symbols 
bool symbOpt(char c){
    string enicks="?*!~$%#";
    return (('A'<=c&&c<='Z')||('a'<=c&&c<='z')||enicks.find(c)!=string::npos);
}


//for choosing spot(1-9)
int chooseSpot(const string& p){
    while(true){
        cout<<p; string s; cin>>s;
        if(s.size()==1&&isdigit(static_cast<unsigned char>(s[0]))){
            int v=s[0]-'0'; if(1<=v&&v<=9) return v;
        }
        cout<<"Enter 1-9.\n";
    }
}


//asking user for personalized symbols to play
char getSymb(const string& p){
    while(true){
        cout<<p; string s; cin>>s;
        if(s.size()==1&&symbOpt(s[0])) return s[0];
        cout<<"Invalid. Use A-Z, a-z, ?, !, *, ~, $, %, #.\n";
    }
}



//asking for architype/class
string architype(const string& p){
    while(true){
        cout<<p; string s; cin>>s;
        for(char& c:s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if(s=="paladin") return "Paladin";
        if(s=="alchemist") return "Alchemist";
        cout<<"Invalid. Choose Paladin or Alchemist.\n";
    }
}


//this one checks availability for paladins ability
vector<int> orthoNbrs(int i){
    int r=i/3,c=i%3; vector<int> v;
    if(r>0) v.push_back((r-1)*3+c);
    if(r<2) v.push_back((r+1)*3+c);
    if(c>0) v.push_back(r*3+c-1);
    if(c<2) v.push_back(r*3+c+1);
    return v;
}


//code for alchemist archetype
bool alchemist(vector<char>& b, char mark){
    cout<<"Alchemist: 1) Regular move   2) Ability(Swap 2 marks)\n> ";
    string s; cin>>s; int ch=(s=="2"?2:1);
    if(ch==1){
        while(true){
            int cell=chooseSpot("Put at (1-9): "); 
            int i=cell-1;
            if(b[i]==' '){ 
                b[i]=mark; 
                return true; 
            }
            cout<<"This cell is taken.\n";
        }
    }else {
        int cnt=0;
        for(char x:b) if(x!=' ') cnt++;
        if(cnt<2){ 
            cout<<"Not enough marks to use.\n"; 
            return false; 
        }
        int a=chooseSpot("First cell (1-9): ")-1; 
        if(b[a]==' '){ cout<<"There is no mark.\n";
            return false; 
        }
        int c=chooseSpot("Second cell (1-9): ")-1; 
        if(b[c]==' '){ 
            cout<<"There is no mark.\n"; 
            return false; 
        }
        if(a==c){ 
            cout<<"Choose two different cells.\n"; 
            return false; 
        }
        if(b[a]==b[c]){ 
            cout<<"Cannot swap two identical marks.\n"; 
            return false; 
        }
        swap(b[a], b[c]); 
        return true;
    }
}



//code for paladin archetype
bool paladin(vector<char>& b, char mark){
    cout<<"Paladin: 1) Regular move   2) Ability(Shift mark)\n> ";
    string s; cin>>s; int ch=(s=="2"?2:1);
    if(ch==1){
        while(true){
            int cell=chooseSpot("Place at (1-9): "); 
            int i=cell-1;
            if(b[i]==' '){ 
                b[i]=mark; 
                return true; 
            }
            cout<<"This cell is taken.\n";
        }
    }else {
        bool any=false; 
        for(char x:b) 
        if(x!=' '){ 
            any=true; 
            break; 
        }
        if(!any){ 
            cout<<"No marks to shift yet.\n"; 
            return false; 
        }
        int from=chooseSpot("From cell (1-9): ")-1; 
        if(b[from]==' '){ 
            cout<<"No mark to shift.\n"; 
            return false; 
        }
        vector<int> pers; 
        for(int j:orthoNbrs(from)) 
        if(b[j]==' ') pers.push_back(j);
        if(pers.empty()){ 
            cout<<"No adjacent empty cells.\n"; 
            return false; 
        }
        cout<<"Choose destination: ["; 
        for(size_t k=0;k<pers.size();++k){ 
            cout<<pers[k]+1; if(k+1<pers.size()) cout<<","; 
        } 
        cout<<"]\n";
        int to=chooseSpot("To cell: ")-1; bool ok=false; 
        for(int j:pers) if(j==to) ok=true;
        if(!ok){ 
            cout<<"Destination must be adjacent & empty.\n"; 
            return false; 
        }
        char m=b[from]; b[from]=' '; 
        b[to]=m; 
        return true;
    }
}



//code for battle game(option 2)
void battle_game(){
    string p1 = "Player 1";
    string p2 = "Player 2";

    char m1=getSymb(p1+", choose your mark: ");
    char m2; do { 
        m2=getSymb(p2+", choose your mark: "); 
        if(m2==m1) cout<<"Marks must be different.\n"; 
    } while(m2==m1);
    string a1=architype(p1+", choose archetype (Paladin/Alchemist): ");
    string a2=architype(p2+", choose archetype (Paladin/Alchemist): ");
    vector<char> b(9,' '); int turn=0;
    while(true){
        printBoard(b);
        bool used=false;
        if(turn%2==0){ 
            cout<<p1<<"'s turn ("<<m1<<") - "<<a1<<"\n"; 
            used = (a1=="Alchemist"?alchemist(b,m1):paladin(b,m1)); 
        }else { 
            cout<<p2<<"'s turn ("<<m2<<") - "<<a2<<"\n"; 
            used = (a2=="Alchemist"?alchemist(b,m2):paladin(b,m2)); 
        }
        if(checkWin(b, turn%2?m2:m1)){ 
            printBoard(b); cout<<(turn%2?p2:p1)<<" wins\n"; 
            return; 
        }
        if(boardCheck(b)){ 
            printBoard(b); cout<<"Tie.\n"; 
            return; 
        }
        if(used) turn++;
    }
}


//code for answerign question yes or no(like if they want to play again for example)
bool answerYN(const string& p){
    while(true){
        cout<<p; string s; cin>>s;
        for(char& c:s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        if(s=="y"||s=="yes") return true;
        if(s=="n"||s=="no")  return false;
        cout<<"Answer yes or no.\n";
    }
}


//main function where everything is connected
int main() {
    while (true) {
        cout<<"Welcome to Tic-Tac-Toe!\n1) Regular\n2) Battle\n> ";
        string s; cin>>s; int ch=(s=="2"?2:1);
        if (ch==1) { play_regular(); }
        else       { battle_game(); }
        if (!answerYN("Play again? (y/n): ")) { 
            cout<<"Thank you for playing!\n"; 
            break; 
        }
    }
    return 0;
}
