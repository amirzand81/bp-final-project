#include <stdio.h>
#include<string.h> 
#include<math.h> 
#include<stdlib.h> 
#include <sys/time.h>

#define Maxline 100

int filteredPlayers = 0 , filteredteams = 0 , goals[2];
char choice[Maxline],NameTeam[Maxline];

struct player{
    int ID;
    int AttackingPower;
    int DefencingPower;
    int value;
    char name[Maxline];
    char foot[6];
    char post[11];
    char state[2];
    char TeamName[Maxline];

}allplayer[800],filteredPlayer[800];

struct team{

    int ID;
    int money;
    int cups;
    char name[Maxline];
    char email[Maxline];
    char password[Maxline];
    char state[Maxline];

}allteam[100],filteredteam[100];

struct Fedrasion{

    char username[Maxline];
    char password[Maxline];
    char LeagueStatus[Maxline];

}admin; 

struct leagueStanding{

    char name[Maxline];
    int Played;
    int Won;
    int Drawn;
    int Lost;
    int GF;
    int GA;
    int GD;
    int Points;

}SubmitedTeams[100],SelectedTeams[4];

void Notifiction(char str[]);
int choose();
void CreatFile(char filename[]);
void back();
void InfoFedrasion();
int CountLines(char fname[]);
int CharToInt(char x[]);
int printRandoms(int lower, int upper);
void printPlayer();
void readPlayers(int mina,int maxa,int mind,int maxd,int minv,int maxv,char state,char foot[],char post[],char team[],char name[],int id);
void EditPlayersInformation(char name[],int id,int type,char newValue[]);
void SwapPlayers(int i,int j);
void sortPlayers(char type,char typesort);
void AddPlayer();
void EditPlayer();
void AdvancedSearch(int a);
void SearchBy();
void DeprivePlayers();
int PasswordSecurity(char pass[]);
void readTeams(char state,char name[],int id,int league);
void AddTeam();
void printteam();
void LeagueButtonTitle();
void EditTeamsInformation(char name[],int id,int type,char newValue[],int newVal);
void BuyPlayer();
int CheckGoalkeeper();
void SellPlayer();
int TransferPosibelity();
void SubmitSquad();
void EditFedrasionInfo(int type,char newValue[]);
void RequestButtonTitle();
void StartLeague();
void Pickweek(int week1[]);
void LotteryGames();
void SelectSquad();
void ReadLeagueStanding();
void PrintLeagueStanding();
void SwapLeagueTeams(int i,int j);
void SortLeagueStanding();
void EditLeagueStanding(char Name[],int Played,int Won,int Drawn,int Lost,int GF,int GA,int GD,int Points);
int CountPlayersNumbers(char Name[]);
void PlayGames(char team1[],char team2[]);
void ReadGameSchedule(int number);
void StartWeekGames(int i);
void PrintGameSchedule();
void Tiredness();
void EndSeason();
void SearchTeamBy();
void EditClubInfo();
void LeagueButton();
void Forgetpassword();
void ExitQuistion();
void UpcomingOpponent();
void ClubManagementAccount();
void DepriveTeams();
void AddTeamButtun();
void FedrasionAccount();
void Login();
void LoginPage();

int main(){

    srand(time(0));

    Notifiction("             Login page");

    while (1)
        LoginPage();

    return 0;
}  

void Notifiction(char str[]){

    system("cls");

    printf("---------------------------------------\n\n");
    printf("%s",str);
    printf("\n\n---------------------------------------\n\n");

}
int choose(){

    time_t start_t, end_t;
    int diff_t;

    time(&start_t);
    scanf("%s",&choice);
    time(&end_t);

    diff_t = difftime(end_t, start_t);

    if(diff_t > 120)
    {
        Notifiction("Login again due to long delays");
        return 1;
    }

    return 0;
}
int CountLines(char fname[]){

    FILE *fptr;
    int ctr = 0;  
    char c; 

    CreatFile(fname);
    fptr = fopen(fname, "r");

    for (c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n') 
            ctr = ctr + 1;

    fclose(fptr);

    return ctr;
}
int CharToInt(char x[]){

    float len = strlen(x),sum = 0,flag = 0;

    if(x[0] == '-'){
        len--;
        flag = 1;
        strcpy(x,&x[1]);
    }

    for (int i = 0; i < len; i++)
        sum += ((int) x[i] - 48) * pow(10,len-i-1);

    if(flag)
        sum *= -1;

    return round(sum);
}
int printRandoms(int lower, int upper){
	int i;
	int num = (rand() % (upper - lower + 1)) + lower;
	
        return num;
}
void printPlayer(){

    char str1[Maxline] ;

    if(filteredPlayers)
    {  
        printf("---------------------------------------------------------------------------------------------------------\n\n");
        printf(" Row   Name            ID    AtPower   DefPower  value     state       foot    TeamName      post\n\n");
        printf("---------------------------------------------------------------------------------------------------------\n");
    }
    
    else
        printf("No player was found!\n");

    for(int i = 0; i < filteredPlayers; i++)
    {
        if(filteredPlayer[i].state[0] == 'f')
            strcpy(str1,"Not Deprived");

        else
            strcpy(str1,"  Deprived");

        if(strcmp(filteredPlayer[i].TeamName,"none") == 0)
            strcpy(filteredPlayer[i].TeamName,"Free Agent");

        printf("%3d    %-15s %-7d %-10d %-7d %-5d %-14s %-7s %-13s %-10s\n",i+1,filteredPlayer[i].name,filteredPlayer[i].ID,filteredPlayer[i].AttackingPower,filteredPlayer[i].DefencingPower,filteredPlayer[i].value,str1,filteredPlayer[i].foot,filteredPlayer[i].TeamName,filteredPlayer[i].post);
        printf("---------------------------------------------------------------------------------------------------------\n");
    }
}
void readPlayers(int mina,int maxa,int mind,int maxd,int minv,int maxv,char state,char foot[],char post[],char team[],char name[],int id){

    FILE *players;
    players = fopen("players.txt","r");

    filteredPlayers = 0;

    int AP,DP,v;

        for (int c = 0; c < CountLines("players.txt") ; c++)
            fscanf(players," %s %s %d %d %d %d %s %s %s ",allplayer[c].state,allplayer[c].TeamName,&allplayer[c].ID,&allplayer[c].AttackingPower,&allplayer[c].DefencingPower,&allplayer[c].value,allplayer[c].foot,allplayer[c].post,allplayer[c].name);

    fclose(players);

	for (int i = 0 ; CountLines("players.txt") > i ; i++)
	{

		AP = allplayer[i].AttackingPower;
		DP = allplayer[i].DefencingPower;
		v = allplayer[i].value;

		if((AP < mina || AP > maxa) || (DP < mind || DP > maxd) || (v < minv || v > maxv))
		    continue;

		if((state == 'f' && allplayer[i].state[0] == 'd') || (state == 'd' && allplayer[i].state[0] == 'f'))
		    continue;

		if(strcmp(foot,"all") != 0)
		    if((foot[0] == 'l' && allplayer[i].foot[0] == 'r') || (foot[0] == 'r' && allplayer[i].foot[0] == 'l'))
		        continue;

		if(strcmp(post,"all") != 0)
		    if((post[0] == 'D' && (allplayer[i].post[0] == 'A' || allplayer[i].post[0] == 'G')) || (post[0] == 'G' && (allplayer[i].post[0] == 'A' || allplayer[i].post[0] == 'D')) || (post[0] == 'A' && (allplayer[i].post[0] == 'D' || allplayer[i].post[0] == 'G')))
		        continue;

		if(strcmp(team,"all") != 0)
			if(strcmp(strlwr(team),strlwr(allplayer[i].TeamName)) != 0)
				continue;

        if(strcmp(name,"all") != 0)
			if(strcmp(strlwr(name),strlwr(allplayer[i].name)) != 0)
				continue;

        if(id != 0)
			if(allplayer[i].ID != id)
				continue;

        strcpy(filteredPlayer[filteredPlayers].state,allplayer[i].state);
        strcpy(filteredPlayer[filteredPlayers].TeamName,allplayer[i].TeamName);
        strcpy(filteredPlayer[filteredPlayers].foot,allplayer[i].foot);
        strcpy(filteredPlayer[filteredPlayers].post,allplayer[i].post);
        strcpy(filteredPlayer[filteredPlayers].name,allplayer[i].name);
		filteredPlayer[filteredPlayers].ID = allplayer[i].ID;
		filteredPlayer[filteredPlayers].DefencingPower = allplayer[i].DefencingPower;
		filteredPlayer[filteredPlayers].AttackingPower = allplayer[i].AttackingPower;
		filteredPlayer[filteredPlayers].value = allplayer[i].value;

		filteredPlayers++;
	}
}
void EditPlayersInformation(char name[],int id,int type,char newValue[]){

    readPlayers(0,100,0,100,0,100,'\0',"all","all","all","all",0);
    int flag = 0;

    for(int i = 0;i < filteredPlayers;i++){

        if(strcmp(strlwr(name),strlwr(filteredPlayer[i].name)) == 0 || id == filteredPlayer[i].ID){

            flag = 1;

            switch(type){
                
                case 1:
                    strcpy(filteredPlayer[i].state,newValue);
                    break;

                case 2:
                    strcpy(filteredPlayer[i].TeamName,newValue);
                    break;

                case 3:
                    strcpy(filteredPlayer[i].name,newValue);
                    break;

                case 4:
                    filteredPlayer[i].DefencingPower = CharToInt(newValue);
                    break;

                case 5:
                    filteredPlayer[i].AttackingPower = CharToInt(newValue);
                    break;

                case 6:
                    filteredPlayer[i].value = CharToInt(newValue);
                    break;

                case 7:
                    strcpy(filteredPlayer[i].foot,newValue);
                    break;

                case 8:
                    strcpy(filteredPlayer[i].post,newValue);
                    break;

            }
        }
    }

    FILE *fplayers;
    fplayers = fopen("players.txt","w");

    for(int i = 0;i < filteredPlayers;i++)
        fprintf(fplayers,"%s %s %d %d %d %d %s %s %s\n",filteredPlayer[i].state,filteredPlayer[i].TeamName,filteredPlayer[i].ID,filteredPlayer[i].AttackingPower,filteredPlayer[i].DefencingPower,filteredPlayer[i].value,filteredPlayer[i].foot,filteredPlayer[i].post,filteredPlayer[i].name);
    
    fclose(fplayers);

    if(flag)
        Notifiction("      Changes made successfully!");

    else
        Notifiction("       The player was not found!");    
}
void SwapPlayers(int i,int j){

    int temp;
    char tempstr[Maxline];

    temp = filteredPlayer[i].value;    
    filteredPlayer[i].value = filteredPlayer[j].value;    
    filteredPlayer[j].value = temp;

    temp = filteredPlayer[i].AttackingPower;    
    filteredPlayer[i].AttackingPower = filteredPlayer[j].AttackingPower;    
    filteredPlayer[j].AttackingPower = temp; 

    temp = filteredPlayer[i].DefencingPower;    
    filteredPlayer[i].DefencingPower = filteredPlayer[j].DefencingPower;    
    filteredPlayer[j].DefencingPower = temp;

    temp = filteredPlayer[i].ID;    
    filteredPlayer[i].ID = filteredPlayer[j].ID;    
    filteredPlayer[j].ID = temp;  

    strcpy(tempstr,filteredPlayer[i].state);    
    strcpy(filteredPlayer[i].state,filteredPlayer[j].state);    
    strcpy(filteredPlayer[j].state,tempstr);    

    strcpy(tempstr,filteredPlayer[i].name);    
    strcpy(filteredPlayer[i].name,filteredPlayer[j].name);    
    strcpy(filteredPlayer[j].name,tempstr); 

    strcpy(tempstr,filteredPlayer[i].TeamName);    
    strcpy(filteredPlayer[i].TeamName,filteredPlayer[j].TeamName);    
    strcpy(filteredPlayer[j].TeamName,tempstr); 

    strcpy(tempstr,filteredPlayer[i].foot);    
    strcpy(filteredPlayer[i].foot,filteredPlayer[j].foot);    
    strcpy(filteredPlayer[j].foot,tempstr); 

    strcpy(tempstr,filteredPlayer[i].post);    
    strcpy(filteredPlayer[i].post,filteredPlayer[j].post);    
    strcpy(filteredPlayer[j].post,tempstr); 
}
void sortPlayers(char type,char typesort){

    if(type == '3' && typesort == 'a')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(filteredPlayer[i].AttackingPower >= filteredPlayer[j].AttackingPower) 
                    SwapPlayers(i,j);  

    }else if(type == '3' && typesort == 'd')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(filteredPlayer[i].AttackingPower <= filteredPlayer[j].AttackingPower) 
                    SwapPlayers(i,j); 

    }else if(type == '4' && typesort == 'a')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(filteredPlayer[i].DefencingPower >= filteredPlayer[j].DefencingPower) 
                    SwapPlayers(i,j);

    }else if(type == '4' && typesort == 'd')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(filteredPlayer[i].DefencingPower <= filteredPlayer[j].DefencingPower) 
                    SwapPlayers(i,j);   

    }else if(type == '2' && typesort == 'a')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(filteredPlayer[i].value >= filteredPlayer[j].value) 
                    SwapPlayers(i,j);         

    }else if(type == '2' && typesort == 'd')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(filteredPlayer[i].value <= filteredPlayer[j].value) 
                    SwapPlayers(i,j);   

    }else if(type == '1' && typesort == 'a')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(strcmp(filteredPlayer[i].name,filteredPlayer[j].name) >= 0) 
                    SwapPlayers(i,j); 

    }else if(type == '1' && typesort == 'd')
        for (int i = 0; i < filteredPlayers; i++){     
            for (int j = i+1; j < filteredPlayers; j++)  
                if(strcmp(filteredPlayer[i].name,filteredPlayer[j].name) <= 0) 
                    SwapPlayers(i,j);         
    }                   
}
void AddPlayer(){

    int ID,AttackingPower = -1,DefencingPower = -1,value = -1;
    char name[Maxline] , foot[Maxline] , post[Maxline] , state[Maxline],TeamName[Maxline];

    printf("---------------------------------------\n\n");
    printf("Please enter the details to add the player :\n\n");

    FILE *fplayers;
    fplayers = fopen("players.txt","a");
                    
    printf("Name : ");
    scanf("%s",&name);

    readPlayers(0,100,0,100,0,100,'\0',"all","all","all",name,0);
    
    if(filteredPlayers)
    {
        Notifiction("     The player name is duplicate!");
        return;
    }

    ID = printRandoms(1000, 9999);

    readPlayers(0,100,0,100,0,100,'\0',"all","all","all","all",0);

    for (int i = 0; i < filteredPlayers; i++)
        while(filteredPlayer[i].ID == ID)
            ID = printRandoms(1000, 9999);

    printf("\nAttackingPower : ");
    while (AttackingPower > 100 || AttackingPower < 0)
        scanf("%d",&AttackingPower); 

    printf("\nDefencingPower : ");
    while (DefencingPower > 100 || DefencingPower < 0)
        scanf("%d",&DefencingPower); 

    printf("\nFoot (right or left) : ");
    scanf("%s",&foot);

    if((strlwr(foot))[0] == 'r')
        strcpy(foot,"right");

    else if(((strlwr(foot))[0] == 'l'))
        strcpy(foot,"left");

    else{
        system("cls");
        printf("---------------------------------------\n\nInvalid inputs ... \n\n    Return to the main!\n\n ");
        return;
    }

    printf("\nIs Goalkeeper (yes or no) : ");
    scanf("%s",&post);

    if(strlwr(post)[0] == 'n')
        (AttackingPower>DefencingPower) ? strcpy(post,"Attacker") : strcpy(post,"Defender");

    else if(strlwr(post)[0] == 'y')
        strcpy(post,"Goalkeeper");

    else{
        system("cls");
        printf("---------------------------------------\n\nInvalid inputs ... \n\n    Return to the main!\n\n ");
        return;
    }

    printf("\nValue : ");
    while (value > 20 || value < 0)
        scanf("%d",&value); 

    fprintf(fplayers,"f none %d %d %d %d %s %s %s\n",ID,AttackingPower,DefencingPower,value,foot,post,name);
    fclose(fplayers);

    system("cls");
    printf("---------------------------------------\n\n     Player successfully added ! \n\n");
}
void EditPlayer(){

    char Editname[Maxline] = "all",newInformation[Maxline];;
    int EditID = 0;

    printf("Edit by ID or name :\n\n1 -> name\n2 -> ID\n\nYour choice is : ");

    scanf("%s",&choice);

    if(choice[0] == '1'){
        printf("\nEnter name : ");
        scanf("%s",&Editname);

    }else if(choice[0] == '2'){
        printf("\nEnter ID : ");
        scanf("%d",&EditID);

    }else{

        Notifiction("     Invalid inputs ... \n\n         Return to the main!");
        return;

    }

    system("cls");
    
    printf("---------------------------------------\n\nWhat information do you want to edit?\n\n");
    printf("1 -> Edit name\n2 -> Edit post\n3 -> Edit foot\n4 -> Edit value\n5 -> Edit AttackingPower\n6 -> Edit DefencingPower\n\nYour choice is : ");

    scanf("%s",&choice);

    if(choice[0] == 49){

        printf("\n\nEnter name : ");
        scanf("%s",&newInformation);
        EditPlayersInformation(Editname,EditID,3,newInformation);

    }else if(choice[0] == 50){

        system("cls");

        printf("---------------------------------------\n\nSelect post\n\n1 -> Attacker\n2 -> Defender\n3 -> Goalkeeper\n\nYour choice is : ");

        scanf("%s",&newInformation);

        if(newInformation[0] == '1')
            strcpy(newInformation,"Attacker");

        else if(newInformation[0] == '2')
            strcpy(newInformation,"Defender");

        else if(newInformation[0] == '3')
            strcpy(newInformation,"Goalkeeper");

        else{
            system("cls");
            printf("---------------------------------------\n\nInvalid inputs ... \n\n    Return to the main!\n\n ");
            return;
        }

        EditPlayersInformation(Editname,EditID,8,newInformation);

    }else if(choice[0] == 51){
                        
        printf("\n\nSelect foot : \n\n1 -> right\n2 -> left\n\nYour choice is : ");

        scanf("%s",&newInformation);

        if(newInformation[0] == '1')
            strcpy(newInformation,"right");

        else if(newInformation[0] == '2')
            strcpy(newInformation,"left");

        else{
            system("cls");
            printf("---------------------------------------\n\nInvalid inputs ... \n\n    Return to the main!\n\n ");
            return;
        }

        EditPlayersInformation(Editname,EditID,7,newInformation);

    }else if(choice[0] == 52){

        printf("\n\nEnter value : ");
        scanf("%s",&newInformation);
                        
        while (CharToInt(newInformation) > 20 || CharToInt(newInformation) < 0)
            scanf("%d",&newInformation); 

        EditPlayersInformation(Editname,EditID,6,newInformation);

    }else if(choice[0] == 53){

        printf("\n\nEnter AttackingPower : ");
        scanf("%s",&newInformation);

        while (CharToInt(newInformation) > 100 || CharToInt(newInformation) < 0)
            scanf("%d",&newInformation); 

        EditPlayersInformation(Editname,EditID,5,newInformation);

    }else if(choice[0] == 54){

        printf("\n\nEnter DefencingPower : ");
        scanf("%s",&newInformation);

        while (CharToInt(newInformation) > 100 || CharToInt(newInformation) < 0)
            scanf("%d",&newInformation); 

        EditPlayersInformation(Editname,EditID,4,newInformation);

    }else{

        system("cls");
        printf("---------------------------------------\n\nInvalid inputs ... \n\n    Return to the main!\n\n ");
        return;
    }
}
void SearchBy(int a){

    char Name[Maxline] = "all";
    int ID = 0;

    printf("---------------------------------------\n\n");
    printf("Please select type of search :\n\n");
    printf("1 -> Search by name\n");
    printf("2 -> Search by ID\n\nYour choice is : ");

    scanf("%s",&choice);

    if(choice[0] == '1'){

        printf("\nEnter name : ");
        scanf("%s",&Name);

    }else if(choice[0] == '2'){

        printf("\nEnter ID : ");
        scanf("%d",&ID);
                
    }else{

        Notifiction("        Invalid input! ");
        return;

    }
            
    system("cls");
    a ? readPlayers(0,100,0,100,0,100,'\0',"all","all","all",Name,ID) : readPlayers(0,100,0,100,0,100,'f',"all","all","all",Name,ID);
    printPlayer();
    back();

}
void AdvancedSearch(int a){

    int AttackingMin,AttackingMax,DefencingMin,DefencingMax,valueMin,valueMax;
    char sortBy[Maxline],sortType[Maxline],foot[Maxline] , post[Maxline] , TeamName[Maxline];

    Notifiction("Advanced search");

    printf("Value Min : ");
    scanf("%d",&valueMin);

    printf("Value Max : ");
    scanf("%d",&valueMax);

    printf("\nAttackingPower Min: ");
    scanf("%d",&AttackingMin);

    printf("AttackingPower Max: ");
    scanf("%d",&AttackingMax);

    printf("\nDefencingPower Min : ");
    scanf("%d",&DefencingMin);

    printf("DefencingPower Max : ");
    scanf("%d",&DefencingMax);

    system("cls");

    printf("---------------------------------------\n\nFoot \n\n1 -> right \n2 -> left \n3 -> all \n\nYour choice is : ");
    scanf("%s",&foot);

    system("cls");

    printf("---------------------------------------\n\nPost : \n\n1 -> Goalkeeper \n2 -> Defender \n3 -> Attacker\n4 -> all\n\nYour choice is :");
    scanf("%s",&post);

    system("cls");

    if(a){
        printf("---------------------------------------\n\nTeanName (Enter s to skip):\n\n");
        scanf("%s",&TeamName);

    }else
        strcpy(TeamName,"none");


    if(strcmp(TeamName,"s") == 0)
        strcpy(TeamName,"all");

    if(foot[0] == '1')
        strcpy(foot,"right");

    else if((foot[0] == '2'))
        strcpy(foot,"left");

    else
        strcpy(foot,"all");


    if(post[0] == '1')
        strcpy(post,"Goalkeeper");

    else if(post[0] == '2')
        strcpy(post,"Defender");

    else if(post[0] == '3')
        strcpy(post,"Attacker");

    else
        strcpy(post,"all");

    system("cls");

    readPlayers(AttackingMin,AttackingMax,DefencingMin,DefencingMax,valueMin,valueMax,'\0',foot,post,"all","all",0);
                        
    printf("---------------------------------------\n\nSort by : \n\n");
    printf("1 -> name \n2 -> value \n3 -> AttackingPower\n4 -> DefencingPower\n\nYour choice : ");

    scanf("%s",&sortBy);
    printf("\nAscending or descending (a or d) : ");
    scanf("%s",&sortType);

    system("cls");
    sortPlayers(sortBy[0],sortType[0]);
    printPlayer();
    back();

}
void DeprivePlayers(){
                        
    char name[Maxline] = "all";
    int ID = 0;

    printf("---------------------------------------\n\n");
    printf("Deprive by ID or name :\n\n");
    printf("1 -> name\n2 -> ID\n3 -> Back\n\nYour choice is : ");

    scanf("%s",&choice);

    if(choice[0] == '1')
    {
        printf("\nEnter name : ");
        scanf("%s",&name);
    }
    
    else if(choice[0] == '2')
    {
        printf("\nEnter ID : ");
        scanf("%d",&ID);
    }
    
    else if(choice[0] == '3')
    {
        Notifiction("         Return to the main!");
        return;
    }
    
    else
    {
        Notifiction("Invalid inputs ... \n\n        Return to the main!");
        return;
    }
    
    system("cls");
    readPlayers(0,100,0,100,10,20,'\0',"all","all","all",name,ID);

    if(filteredPlayer[0].state[0] == 'f' && filteredPlayers)
        EditPlayersInformation(name,ID,1,"d");
                        
    else
        EditPlayersInformation(name,ID,1,"f");
}
void back(){

    char back[Maxline];
    printf("\nPress b to back : ");
    scanf("%s",&back);

}
int PasswordSecurity(char pass[]){

    char pass1[Maxline] , pass2[Maxline];

    strcpy(pass1,pass);
    strcpy(pass2,pass);

    if((strcmp(strlwr(pass1),pass) == 0 ) || (strcmp(strupr(pass1),pass) == 0 ) || strlen(pass) < 7)
        return 1;
    
    return 0;
}
void readTeams(char state,char name[],int id,int league){

    CreatFile("Teams.txt");

    FILE *teams;
    teams = fopen("Teams.txt","r");

    filteredteams = 0;

    int c,i = -1;
    char str[Maxline],*str1,*str2;

    while (!feof(teams)){

        i++;

        for (int c = 1; c < 8; c++){

            fscanf(teams,"%s",str);

            switch(c){

                case 1:
                    allteam[i].ID = CharToInt(str);
                    break;

                case 2:
                    allteam[i].money = CharToInt(str);
                    break;

                case 3:
                    strcpy(allteam[i].name,str);
                    break;

                case 4:
                    strcpy(allteam[i].email,str);
                    break;

                case 5:
                    strcpy(allteam[i].password,str);
                    break;

                case 6:
                    strcpy(allteam[i].state,str);
                    break;

                case 7:
                    allteam[i].cups = CharToInt(str);
                    break;
        }
    }
}

    fclose(teams);

    i--;
	for (;i+1;i--){

        if(state != '\0')
            if((state == 'f' && allteam[i].state[0] == 'd') || (state == 'd' && allteam[i].state[0] == 'f'))
                continue;
        
        str1 = strdup(allteam[i].name);
        str2 = strdup(name);

        if(strcmp(name,"all") != 0)
			if(strcmp(strlwr(str2),strlwr(str1)) != 0)
				continue;

        if(id != 0)
			if(allteam[i].ID != id)
				continue;

        if(league)
            for(int j = 0; j < 4; j++)
                if(strcmp(SubmitedTeams[j].name,allteam[i].name))
                    continue;
            
        strcpy(filteredteam[filteredteams].state,allteam[i].state);
        strcpy(filteredteam[filteredteams].email,allteam[i].email);
        strcpy(filteredteam[filteredteams].password,allteam[i].password);
        strcpy(filteredteam[filteredteams].name,allteam[i].name);
		filteredteam[filteredteams].ID = allteam[i].ID;
		filteredteam[filteredteams].money = allteam[i].money;
		filteredteam[filteredteams].cups = allteam[i].cups;

		filteredteams++;

    }
}
void AddTeam(){

    int ID;
    char name[Maxline],email[Maxline],password[Maxline];

    printf("---------------------------------------\n\n");
    printf("Please enter the details to add the team :\n\n");

    FILE *fteam;
    fteam = fopen("Teams.txt","a");
                    
    printf("Team-Name : ");
    scanf("%s",&name);

    readTeams('\0',name,0,0);

    if(filteredteams)
    {
        Notifiction("     The team name is duplicate!");
        return;
    }

    ID = printRandoms(100, 999);
    
    readTeams('\0',"all",0,0);

    for (int i = 0; i < filteredteams; i++)
        while(allteam[i].ID == ID)
            ID = printRandoms(1000, 9999);

    printf("\nHead coach email : ");
    scanf("%s",&email); 

    char* pointer = strchr(email,'@');
    
    while(!((pointer - email) >= 0 && (pointer - email) < strlen(email)))
    {
        printf("\nInvalid email ! Please re-enter email : ");
        scanf("%s",&email);        
        pointer = strchr(email,'@');
    }

    fprintf(fteam,"%d 100 %s %s %s f 0\n",ID,name,email,name);
    fclose(fteam);
                    
    system("cls");
    printf("---------------------------------------\n\n     Team successfully added ! \n\n");
}
void printteam(){

    char str1[Maxline];

    if(filteredteams)
    { 
        printf("------------------------------------------------------------------------------------------------------\n\n");
        printf(" Row   Name            ID     money      state       PlayerNumber   cups  Email\n\n");
        printf("------------------------------------------------------------------------------------------------------\n");

        for(int i = 0 ; i < filteredteams ; i++)
        {
            if(filteredteam[i].state[0] == 'f')
                strcpy(str1,"Not Deprived");

            else
                strcpy(str1,"  Deprived");

            readPlayers(0,100,0,100,0,100,'\0',"all","all",filteredteam[i].name,"all",0);

            printf("%3d    %-15s %-7d %-6d %-19s %-10d %-4d %-7s\n",i+1,filteredteam[i].name,filteredteam[i].ID,filteredteam[i].money,str1,filteredPlayers,filteredteam[i].cups,filteredteam[i].email);
            printf("------------------------------------------------------------------------------------------------------\n");
        }
    }
    
    else
        printf("No team was found!\n");
}
void InfoFedrasion(){

    char str[Maxline];
    FILE *Fedrasion;
    Fedrasion = fopen("Fedrasion.txt","r");
    fscanf(Fedrasion,"%s",str);
    strcpy(admin.username,str);
    fscanf(Fedrasion,"%s",str);
    strcpy(admin.password,str);
    fscanf(Fedrasion,"%s",str);
    strcpy(admin.LeagueStatus,str);

    if(strcmp("none",admin.LeagueStatus))   
        for(int i = 0; i < 4; i++){

            fscanf(Fedrasion,"%s",str);
            strcpy(SelectedTeams[i].name,str);

        }

    
    fclose(Fedrasion);
    
}
void LeagueButtonTitle(){
    
    InfoFedrasion();

    if(strcmp(admin.LeagueStatus,"none") == 0)
        printf("5 -> Start League");

    else if(strcmp(admin.LeagueStatus,"open") == 0)
        printf("5 -> Open / Close Transfer Window");

    else if(strcmp(admin.LeagueStatus,"close") == 0)
        printf("5 -> Open / Close Transfer Window");

    else if(strcmp(admin.LeagueStatus,"1") == 0)
        printf("5 -> Start Week 1-th Games");

    else if(strcmp(admin.LeagueStatus,"2") == 0)
        printf("5 -> Start Week 2-th Games");
    
    else if(strcmp(admin.LeagueStatus,"3") == 0)
        printf("5 -> Start Week 3-th Games");

    else if(strcmp(admin.LeagueStatus,"41") == 0 || strcmp(admin.LeagueStatus,"42") == 0)
        printf("5 -> Start Week 4-th Games");

    else if(strcmp(admin.LeagueStatus,"5") == 0)
        printf("5 -> Start Week 5-th Games");
    
    else if(strcmp(admin.LeagueStatus,"6") == 0)
        printf("5 -> Start Week 6-th Games");

    else if(strcmp(admin.LeagueStatus,"end") == 0)
        printf("5 -> End Season and Announce The Champion");
}
void BuyPlayer(){

    if(TransferPosibelity() == 0)
        {
            Notifiction("This feature is not currently available !");
            return;
        }

    while (1)
    {   
        printf("---------------------------------------\n\n");
        printf("1 -> Show all players without order and category\n2 -> Search by name or ID\n3 -> Advanced search\n4 -> Back\n\nYour choice is : ");

        choose() ? LoginPage() : system("cls");

        if(choice[0] == '1')
        {
            readPlayers(0,100,0,100,0,100,'f',"all","all","none","all",0);
            printPlayer();
        }
        
        else if(choice[0] == '2')
            SearchBy(0);
                
        else if(choice[0] == '3')
            AdvancedSearch(0);
        
        else if(choice[0] == '4')
        {
            Notifiction("         Return to the main!");
            break;
        }
        
        else
        {
            Notifiction("Invalid inputs ... \n\n        Return to the main!");
            break;
        }

    int ID;

    readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",0);
    if(filteredPlayers < 8){

        printf("\nEnter playerID to buy : ");
        scanf("%d",&ID);

        readTeams('\0',NameTeam,0,0);
        readPlayers(0,100,0,100,0,100,'f',"all","all","all","all",ID);

        if(filteredPlayers == 0)
            {
                Notifiction("       No players not found !");
                return;
            }

        if(filteredteam[0].money >= filteredPlayer[0].value){ 

            readPlayers(0,100,0,100,0,100,'f',"all","all","all","all",ID);                    

            EditPlayersInformation("all",ID,2,NameTeam);
            EditTeamsInformation(NameTeam,0,1,"",filteredteam[0].money - filteredPlayer[0].value);

            Notifiction("The player was successfully buyed !");

        }else{

            Notifiction("       Money is not enough !");
            return;
        }

    }else{

        Notifiction("   Maximum number of players is 8 !");
        return;
        }
    }
}    
void EditTeamsInformation(char name[],int id,int type,char newValue[],int newVal){

    readTeams('\0',"all",0,0);
    int flag = 0;
    char *str1,*str2;

    for(int i = 0;i < filteredteams;i++){

        str1 = strdup(filteredteam[i].name);
        str2 = strdup(name);

        if(strcmp(strlwr(str2),strlwr(str1)) == 0 || id == filteredteam[i].ID){

            flag = 1;

            switch(type){

                case 1:
                    filteredteam[i].money = newVal;
                    break;

                case 2:
                    strcpy(filteredteam[i].name,newValue);
                    break;

                case 3:
                    strcpy(filteredteam[i].email,newValue);
                    break;

                case 4:
                    strcpy(filteredteam[i].password,newValue);
                    break;

                case 5:
                    strcpy(filteredteam[i].state,newValue);
                    break;

                case 6:
                    filteredteam[i].cups = newVal;
                    break;
            }
        }
    }

        FILE *fteam;
        fteam = fopen("Teams.txt","w");

    for(int i = 0;i < filteredteams;i++)
        fprintf(fteam,"%d %d %s %s %s %s %d\n",filteredteam[i].ID,filteredteam[i].money,filteredteam[i].name,filteredteam[i].email,filteredteam[i].password,filteredteam[i].state,filteredteam[i].cups);
    
        fclose(fteam);

    if(flag)
        Notifiction("      Changes made successfully!");

    else
        Notifiction("       The Team was not found!");    

}
int CheckGoalkeeper(){
    
    int count = 0;
    char str[Maxline];

    FILE *Req;
    Req = fopen("RequestLeague.txt","r");

    for(int i = 0 ; i < CountLines("RequestLeague.txt") ;i++){

        fscanf(Req,"%s",str);
        readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,str,0);

        if(filteredPlayers == 0)
            continue;
        
        else
            if(strcmp(filteredPlayer[0].post,"Goalkeeper") == 0)
                count++;
    }
    
    fclose(Req);
    return count;
}
void SellPlayer(){

    int ID;

    if(TransferPosibelity() == 0)
    {
        Notifiction("This feature is not currently available !");
        return;
    }

    readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",0);
    sortPlayers('2','d');
    printPlayer();

    printf("\nEnter playerID to sell : ");
    scanf("%d",&ID);

    readPlayers(0,100,0,100,0,100,'\0',"all","all","none","all",ID);         

    if(filteredPlayers == 0)
    {
        Notifiction("         No player was found !");
        return;
    }

    EditPlayersInformation("all",ID,2,"none");
    readTeams('\0',NameTeam,0,0);

    Notifiction("The player was successfully selled !");

    EditTeamsInformation(NameTeam,0,1,"",filteredteam[0].money + filteredPlayer[0].value);

}
void CreatFile(char filename[]){

    FILE *fp;
    fp = fopen(filename,"a");
    fclose(fp);
    
}
int TransferPosibelity(){

   InfoFedrasion();

   if(strcmp(admin.LeagueStatus,"none") == 0 || strcmp(admin.LeagueStatus,"close") == 0)
        return 1;

    return 0;

}
void SubmitSquad(){

    char str[Maxline];
    CreatFile("RequestLeague.txt");

    int flag = 0;

    if(strcmp(admin.LeagueStatus,"none"))
    {
        InfoFedrasion();

        for(int i = 0;4 > i;i++)
            if(strcmp(strlwr(SelectedTeams[i].name),strlwr(NameTeam)) == 0)
                flag = 1;
            
        if(flag == 0)
        {
            Notifiction("    You are not part of this league!");
            return;
        }
    }

    readTeams('\0',NameTeam,0,0);

    if(strcmp(filteredteam[0].state,"d") == 0)
    {
        Notifiction("      You deprived from the league!");
        return;
    }

    readPlayers(0,100,0,100,10,20,'\0',"all","all",NameTeam,"all",0);
    if(filteredPlayers == 8){

    FILE *Request;
    Request = fopen("RequestLeague.txt","a+");

    while (!feof(Request))
    {
        fscanf(Request,"%s",str);

        if(strcmp(NameTeam,str) == 0)
        {
            Notifiction("  You have already submitted a request !");
            return;
        }
    }
    

    fprintf(Request,"%s\n",NameTeam);
    Notifiction("Your request has been sent successfully !");

    fclose(Request);

    }
    
    else
        Notifiction("Your team members are not complete !");
}
void EditFedrasionInfo(int type,char newValue[]){

    InfoFedrasion();

    if(type == 2)
        strcpy(admin.LeagueStatus,newValue);

    FILE *Fedrasion = fopen("Fedrasion.txt","w");
    fprintf(Fedrasion,"Admin\n%s\n%s\n%s %s %s %s",admin.password,admin.LeagueStatus,SelectedTeams[0].name,SelectedTeams[1].name,SelectedTeams[2].name,SelectedTeams[3].name);
    fclose(Fedrasion);
}
void RequestButtonTitle(){

    InfoFedrasion();

    int flag = 0;
    
    for(int i = 0;4 > i;i++)
        if(strcmp(strlwr(SelectedTeams[i].name),strlwr(NameTeam)) == 0)
            flag = 1;

    if((strcmp(admin.LeagueStatus,"none") != 0 && flag) || (strcmp(admin.LeagueStatus,"41") != 0 && flag))
        printf("3 -> Select Squad\n");
         
    else
        printf("3 -> Submit Squad\n");
        
}
void SearchTeamBy(){

    char Name[Maxline] = "all";
    int ID = 0;

    printf("---------------------------------------\n\n");
    printf("Please select type of search :\n\n");
    printf("1 -> Search by name\n");
    printf("2 -> Search by ID\n\nYour choice is : ");

    scanf("%s",&choice);

    if(choice[0] == '1')
    {
        printf("\nEnter name : ");
        scanf("%s",&Name);
    }
    
    else if(choice[0] == '2')
    {
        printf("\nEnter ID : ");
        scanf("%d",&ID);       
    }
    
    else
    {
        Notifiction("        Invalid input! ");
        return;
    }
            
    system("cls");
    readTeams('\0',Name,ID,0);
    printteam();
    back();
}
void StartLeague(){

    system("cls");
    int len = CountLines("RequestLeague.txt") , i = -1,index;

    if(len < 4)
    {
        Notifiction("    You can not start the league !\n\n     The min number of teams is 4 ");
        return;
    }
    
    else if(len > 4)
    {
        FILE *Request;
        Request = fopen("RequestLeague.txt","r");

        for(int i = 0;len > i;i++)
            fscanf(Request,"%s",SubmitedTeams[i].name);

        fclose(Request);

        readTeams('\0',"all",0,1);
        printteam();

        printf("\nPlease enter ID of team :\n\n");

        for (int i = 0; i < 4; i++)
        {
            printf("TeamID %d : ",i+1);
            
            scanf("%d",&index);
            readTeams('f',"all",index,0);

            while(!(filteredteams))
            { 
                printf("ID is invalid ...\nPlease enter again : ");
                scanf("%d",&index);
                readTeams('f',"all",index,0);
            }

            strcpy(SelectedTeams[i].name,filteredteam[0].name);
        }  
    }
    
    else
    {

        FILE *Request;
        Request = fopen("RequestLeague.txt","r");

        for(int i = 0;len > i;i++)
            fscanf(Request,"%s",SelectedTeams[i].name);

        fclose(Request);

        EditFedrasionInfo(2,"1");
    }

    Notifiction("   The league started successfully!");
    EditFedrasionInfo(2,"1");

    FILE *GameSchedule = fopen("GameSchedule.txt","w");
    fclose(GameSchedule);

    LotteryGames();
    LotteryGames();

    FILE *Req = fopen("RequestLeague.txt","w");
    fclose(Req);

    FILE *Tired = fopen("Tiredness.txt","w");
    fclose(Tired);

    FILE *LeagueStanding = fopen("LeagueStanding.txt","w");

    for(int i = 0;len > i;i++)
        fprintf(LeagueStanding,"%s 0 0 0 0 0 0 0 0\n",SelectedTeams[i].name);

    fclose(LeagueStanding);
}
void Pickweek(int week1[]){

    for(int i = 0 ; i < 4 ; i++){
        week1[i] = printRandoms(1,4);

    for(int k = 0 ; k < i ; k++)
        while (week1[i] == week1[k]){
    week1[i] = printRandoms(1,4);
    k = 0;

        }
    }
}
void LotteryGames(){

    FILE *Request;
    Request = fopen("RequestLeague.txt","r");

    for(int i = 0;4 > i;i++)
        fscanf(Request,"%s",SelectedTeams[i].name);

    fclose(Request);

    int week1[4];
    int week2[4];
    int week3[4];

    Pickweek(week1);
    Pickweek(week2);

    while(

        (week2[0] == week1[0] && week2[1] == week1[1]) ||
        (week2[0] == week1[1] && week2[1] == week1[0]) ||
        (week2[0] == week1[2] && week2[1] == week1[3]) ||
        (week2[0] == week1[3] && week2[1] == week1[2])
        
    )Pickweek(week2);

    Pickweek(week3);
    
    while(

        (week3[0] == week1[0] && week3[1] == week1[1]) ||
        (week3[0] == week1[1] && week3[1] == week1[0]) ||
        (week3[0] == week1[2] && week3[1] == week1[3]) ||
        (week3[0] == week1[3] && week3[1] == week1[2]) ||
        (week3[0] == week2[0] && week3[1] == week2[1]) ||
        (week3[0] == week2[1] && week3[1] == week2[0]) ||
        (week3[0] == week2[2] && week3[1] == week2[3]) ||
        (week3[0] == week2[3] && week3[1] == week2[2])

    )Pickweek(week3);

    FILE *GameSchedule;
    GameSchedule = fopen("GameSchedule.txt","a");

    InfoFedrasion();

    for(int i = 0 ; i < 4 ; i++){

        if(i == 0)
            fprintf(GameSchedule,SelectedTeams[week1[i] - 1].name); 

        else if(i == 1)
            fprintf(GameSchedule," - - %s\n",SelectedTeams[week1[i] - 1].name); 

        else if(i == 2)
            fprintf(GameSchedule,"%s",SelectedTeams[week1[i] - 1].name);

        else if(i == 3)
            fprintf(GameSchedule," - - %s\n",SelectedTeams[week1[i] - 1].name);
 
    }

    for(int i = 0 ; i < 4 ; i++){

        if(i == 0)
            fprintf(GameSchedule,SelectedTeams[week2[i] - 1].name); 

        else if(i == 1)
            fprintf(GameSchedule," - - %s\n",SelectedTeams[week2[i] - 1].name); 

        else if(i == 2)
            fprintf(GameSchedule,"%s",SelectedTeams[week2[i] - 1].name);

        else if(i == 3)
            fprintf(GameSchedule," - - %s\n",SelectedTeams[week2[i] - 1].name);
    }

    for(int i = 0 ; i < 4 ; i++){

        if(i == 0)
            fprintf(GameSchedule,SelectedTeams[week3[i] - 1].name); 

        else if(i == 1)
            fprintf(GameSchedule," - - %s\n",SelectedTeams[week3[i] - 1].name); 

        else if(i == 2)
            fprintf(GameSchedule,"%s",SelectedTeams[week3[i] - 1].name);

        else if(i == 3)
            fprintf(GameSchedule," - - %s\n\n",SelectedTeams[week3[i] - 1].name);
    }

    fclose(GameSchedule);
}
void SelectSquad(){

    char str[Maxline],*str1,*str2;
    int count = 0;

    FILE *req;
    req = fopen("RequestLeague.txt","r");

    str1 = strdup(NameTeam);

    for (int i = 0 ; i < CountLines("RequestLeague.txt") ; i++)
    {
        fscanf(req,"%s",str);

        readPlayers(0,100,0,100,0,100,'\0',"all","all","all",str,0);

        str2 = strdup(filteredPlayer[0].TeamName);
        
        if(strcmp(strlwr(str1),strlwr(str2)) == 0)
            count++;
    }

    if(count == 5)
    {
        Notifiction("You have confirmed your final composition!");
        return;
    }

    int index,number = 1;

    readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",0);
    printPlayer();

    printf("\nPlease enter ID of players :\n\n");

    for ( ; number <= 5 ; ){

        printf("PlayerID %d : ",number);
            
        scanf("%d",&index);
        readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",index);

        while(!(filteredPlayers))
        { 
            printf("ID is invalid ...\nPlease enter again ");
            scanf("%d",&index);
            readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",index);
        }

        readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",index);

        if(strcmp(filteredPlayer[0].state,"d") == 0)
        {
            printf("This player is deprived from league !\nPlease enter again ");
            continue;
        }

        if(strcmp(filteredPlayer[0].post,"Goalkeeper") == 0 && CheckGoalkeeper())
        {
            printf("You have a goalkeeper in your team !\nPlease enter again ");
            continue;
        }

        readPlayers(0,100,0,100,0,100,'\0',"all","all",NameTeam,"all",index);

        FILE *Request;
        Request = fopen("RequestLeague.txt","a");
        fprintf(Request,"%s\n",filteredPlayer[0].name);
        fclose(Request);
        number++; 
    }
    
    Notifiction("   The final composition was saved!");
}
void ReadLeagueStanding(){

    FILE *LeagueStanding;
    LeagueStanding = fopen("LeagueStanding.txt","r");

    for(int i = 0 ; i < CountLines("LeagueStanding.txt") ; i++)
        fscanf(LeagueStanding," %s %d %d %d %d %d %d %d %d",SelectedTeams[i].name,&SelectedTeams[i].Played,&SelectedTeams[i].Won,&SelectedTeams[i].Drawn,&SelectedTeams[i].Lost,&SelectedTeams[i].GF,&SelectedTeams[i].GA,&SelectedTeams[i].GD,&SelectedTeams[i].Points);
}
void PrintLeagueStanding(){

    system("cls");

    printf("-------------------------------------------------------------------------------------\n\n");
    printf(" Row   Team-Name         Played   Won  Drawn  Lost   GF    GA   GD   Points\n\n");
    printf("-------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 4; i++)
    {
        printf("  %d    %-19s %-7d %-5d %-5d %-5d %-5d %-5d %-5d %-3d\n",i+1,SelectedTeams[i].name,SelectedTeams[i].Played,SelectedTeams[i].Won,SelectedTeams[i].Drawn,SelectedTeams[i].Lost,SelectedTeams[i].GF,SelectedTeams[i].GA,SelectedTeams[i].GD,SelectedTeams[i].Points);
        printf("-------------------------------------------------------------------------------------\n");
    }
}
void SwapLeagueTeams(int i,int j){

    int temp;
    char tempstr[Maxline];

    temp = SelectedTeams[i].Drawn;    
    SelectedTeams[i].Drawn = SelectedTeams[j].Drawn;  
    SelectedTeams[j].Drawn = temp;

    temp = SelectedTeams[i].GA;    
    SelectedTeams[i].GA = SelectedTeams[j].GA;  
    SelectedTeams[j].GA = temp;

    temp = SelectedTeams[i].GD;    
    SelectedTeams[i].GD = SelectedTeams[j].GD;  
    SelectedTeams[j].GD = temp;

    temp = SelectedTeams[i].Lost;    
    SelectedTeams[i].Lost = SelectedTeams[j].Lost;  
    SelectedTeams[j].Lost = temp;

    temp = SelectedTeams[i].Played;    
    SelectedTeams[i].Played = SelectedTeams[j].Played;  
    SelectedTeams[j].Played = temp;

    temp = SelectedTeams[i].Points;    
    SelectedTeams[i].Points = SelectedTeams[j].Points;  
    SelectedTeams[j].Points = temp;

    temp = SelectedTeams[i].GF;    
    SelectedTeams[i].GF = SelectedTeams[j].GF;  
    SelectedTeams[j].GF = temp;

    temp = SelectedTeams[i].Won;    
    SelectedTeams[i].Won = SelectedTeams[j].Won;  
    SelectedTeams[j].Won = temp;

    strcpy(tempstr,SelectedTeams[i].name);    
    strcpy(SelectedTeams[i].name,SelectedTeams[j].name);    
    strcpy(SelectedTeams[j].name,tempstr);    

}
void SortLeagueStanding(){

    ReadLeagueStanding();

    for (int i = 0; i < 4; i++){     
        for (int j = i+1; j < 4; j++)  
            if(SelectedTeams[i].Points <= SelectedTeams[j].Points) 
                SwapLeagueTeams(i,j);  
    }

    for (int i = 0; i < 4; i++){     
        for (int j = i+1; j < 4; j++)  
            if(SelectedTeams[i].Points == SelectedTeams[j].Points) 
                if(SelectedTeams[i].GD <= SelectedTeams[j].GD)
                    SwapLeagueTeams(i,j);  
    }

    for (int i = 0; i < 4; i++){     
        for (int j = i+1; j < 4; j++)  
            if(SelectedTeams[i].Points == SelectedTeams[j].Points && SelectedTeams[i].GD == SelectedTeams[j].GD) 
                if(SelectedTeams[i].GF <= SelectedTeams[j].GF)
                    SwapLeagueTeams(i,j);  
    }
}
void EditLeagueStanding(char Name[],int Played,int Won,int Drawn,int Lost,int GF,int GA,int GD,int Points){

    ReadLeagueStanding();

    int i = 0;
    for( ; i < 4; i++)  
        if(strcmp(Name,SelectedTeams[i].name) == 0)
            break; 

    SelectedTeams[i].Played += Played;
    SelectedTeams[i].Won += Won;
    SelectedTeams[i].Drawn += Drawn;
    SelectedTeams[i].Lost += Lost;
    SelectedTeams[i].GF += GF;
    SelectedTeams[i].GA += GA;
    SelectedTeams[i].GD += GD;
    SelectedTeams[i].Points += Points;

    FILE *LeagueStanding = fopen("LeagueStanding.txt","w");

    for(int i = 0 ; i < 4; i++)  
        fprintf(LeagueStanding,"%s %d %d %d %d %d %d %d %d\n",SelectedTeams[i].name,SelectedTeams[i].Played,SelectedTeams[i].Won,SelectedTeams[i].Drawn,SelectedTeams[i].Lost,SelectedTeams[i].GF,SelectedTeams[i].GA,SelectedTeams[i].GD,SelectedTeams[i].Points);

    fclose(LeagueStanding);
}
int CountPlayersNumbers(char Name[]){

    char str[Maxline],*str1,*str2;
    int count = 0;

    CreatFile("Tiredness.txt");

    FILE *Tired;
    Tired = fopen("Tiredness.txt","r");

    str1 = strdup(Name);

    for (int i = 0 ; i < CountLines("Tiredness.txt") ; i++){
        fscanf(Tired,"%s",str);
        
        str2 = strdup(str);
        
        if(strcmp(strlwr(str1),strlwr(str2)) == 0)
            count++;
    }

    fclose(Tired);

    return count;
}
void Tiredness(){

    int counts[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char str[20][Maxline];

    FILE *Request;
    Request = fopen("RequestLeague.txt","r");

    for (int i = 0; i < 20; i++)
    {
        fscanf(Request,"%s",str[i]);
        counts[i] += CountPlayersNumbers(str[i]);
    }

    fclose(Request);

    FILE *Req;
    Req = fopen("Tiredness.txt","w");

    for(int i = 0; i < 20; i++)
        for(int j = 0; j <= counts[i]; j++)
            fprintf(Req,"%s\n",str[i]);

    fclose(Req);

}
void PlayGames(char team1[],char team2[]){
    
    char str[Maxline],*str1,*str2;
    int Atack1 = 0 , Atack2 = 0, Defe1 = 0 , Defe2 = 0;

    FILE *Request;
    Request = fopen("RequestLeague.txt","r");

    for (int i = 0 ; i < CountLines("RequestLeague.txt") ; i++){
        fscanf(Request,"%s",str);
        
        readPlayers(0,100,0,100,10,20,'\0',"all","all","all",str,0);

        str1 = strdup(filteredPlayer[0].TeamName);
        str2 = strdup(team1);

        if(strcmp(strlwr(str1),strlwr(str2)) == 0){
            Atack1 += (filteredPlayer[0].AttackingPower - 5 * CountPlayersNumbers(filteredPlayer[0].name));
            Defe1 += (filteredPlayer[0].DefencingPower - 5 * CountPlayersNumbers(filteredPlayer[0].name));
    }
        
        str2 = strdup(team2);

        if(strcmp(strlwr(str1),strlwr(str2)) == 0){
            Atack2 += (filteredPlayer[0].AttackingPower - 5 * CountPlayersNumbers(filteredPlayer[0].name));
            Defe2 += (filteredPlayer[0].DefencingPower - 5 * CountPlayersNumbers(filteredPlayer[0].name));
    }
}

    fclose(Request);

    if(Atack1 - Defe2 < 0)
        goals[0] = 0;
    
    else
        goals[0] = (Atack1 - Defe2) / 100;

    if(Atack2 - Defe1 < 0)
        goals[1] = 0;
    
    else
        goals[1] = (Atack2 - Defe1) / 100;


    if(goals[0] > goals[1]){

        EditLeagueStanding(team1,1,1,0,0,goals[0],goals[1],goals[0] - goals[1],3);
        EditLeagueStanding(team2,1,0,0,1,goals[1],goals[0],goals[1] - goals[0],0);

        readTeams('\0',team1,0,0);
        EditTeamsInformation(team1,0,1,"",filteredteam[0].money + 5);

        readTeams('\0',team2,0,0);
        EditTeamsInformation(team2,0,1,"",filteredteam[0].money + 1);

    }else if(goals[0] < goals[1]){

        EditLeagueStanding(team1,1,0,0,1,goals[0],goals[1],goals[0] - goals[1],0);
        EditLeagueStanding(team2,1,1,0,0,goals[1],goals[0],goals[1] - goals[0],3);

        readTeams('\0',team1,0,0);
        EditTeamsInformation(team1,0,1,"",filteredteam[0].money + 1);

        readTeams('\0',team2,0,0);
        EditTeamsInformation(team2,0,1,"",filteredteam[0].money + 5);
    
    }else{
        
        EditLeagueStanding(team1,1,0,1,0,goals[0],goals[1],goals[0] - goals[1],1);
        EditLeagueStanding(team2,1,0,1,0,goals[1],goals[0],goals[1] - goals[0],1);

        readTeams('\0',team1,0,0);
        EditTeamsInformation(team1,0,1,"",filteredteam[0].money + 3);

        readTeams('\0',team2,0,0);
        EditTeamsInformation(team2,0,1,"",filteredteam[0].money + 3);
    
    }
}
void ReadGameSchedule(int number){

    char teams1[12][Maxline] , teams2[12][Maxline] , goals1[12][Maxline] , goals2[12][Maxline] , str1[Maxline] , str2[Maxline] , str[Maxline];

    FILE *GameSchedule = fopen("GameSchedule.txt","r");

    for (int i = 0; i < 12; i++)
        fscanf(GameSchedule,"%s%s%s%s",teams1[i],goals1[i],goals2[i],teams2[i]);
    
    fclose(GameSchedule);

    PlayGames(teams1[(2*number)-2],teams2[(2*number)-2]);

    sprintf(str1, "%d", goals[0]);
    sprintf(str2, "%d", goals[1]);
    strcpy(goals1[(2*number)-2],str1);
    strcpy(goals2[(2*number)-2],str2);

    PlayGames(teams1[(2*number)-1],teams2[(2*number)-1]);

    sprintf(str1, "%d", goals[0]);
    sprintf(str2, "%d", goals[1]);
    strcpy(goals1[(2*number)-1],str1);
    strcpy(goals2[(2*number)-1],str2);

    FILE *GSchedule = fopen("GameSchedule.txt","w");

    for (int i = 0; i < 12; i++)
        fprintf(GSchedule,"%s %s %s %s\n",teams1[i],goals1[i],goals2[i],teams2[i]);
    
    fclose(GSchedule);
}
void StartWeekGames(int i){

    char str[Maxline];

    if(CountLines("RequestLeague.txt") != 20)
    {
        Notifiction("You can not start the games of this week !\n\n Not all teams have announced their readiness ");
        return;
    }

    InfoFedrasion();

    if(i == 1)
        EditFedrasionInfo(2,"2");

    else if(i == 2)
        EditFedrasionInfo(2,"3");

    else if(i == 3)
        EditFedrasionInfo(2,"open");

    else if(i == 4)
        EditFedrasionInfo(2,"5");

    else if(i == 5)
        EditFedrasionInfo(2,"6");
    
    else if(i == 6)
        EditFedrasionInfo(2,"end");

    Tiredness();

    ReadGameSchedule(i);

    system("cls");
    printf("---------------------------------------\n\n The games of the %d week were played!\n\n---------------------------------------\n\n",i);
    
    FILE *Req = fopen("RequestLeague.txt","w");
    fclose(Req);
}
void PrintGameSchedule(){

    char teams1[12][Maxline] , teams2[12][Maxline] , goals1[12][Maxline] , goals2[12][Maxline];

    FILE *GameSchedule = fopen("GameSchedule.txt","r");

    for (int i = 0; i < 12; i++)
        fscanf(GameSchedule,"%s%s%s%s",teams1[i],goals1[i],goals2[i],teams2[i]);
    
    fclose(GameSchedule);

    system("cls");

    for (int i = 1; i <= 6; i++)
    {
        printf("-------------------------------------------------\n\nGames of the Week %d :\n\n",i);
        printf("      %-15s %-2s %-7s %-20s\n",teams1[2*i-2],goals1[2*i-2],goals2[2*i-2],teams2[2*i-2]);
        printf("      %-15s %-2s %-7s %-20s\n\n",teams1[2*i-1],goals1[2*i-1],goals2[2*i-1],teams2[2*i-1]);
    }

    printf("-------------------------------------------------\n");
}
void Login(){

    if(CountLines("Fedrasion.txt") == 0)
    {
        FILE *Fedrasion = fopen("Fedrasion.txt","a");
        fprintf(Fedrasion,"%s \n%s\nnone\n","Admin","Admin");
        fclose(Fedrasion);
    }

    char username[Maxline],password[Maxline];
    InfoFedrasion();

    Notifiction("Please enter your username and password :");
            
    printf("Username : ");
    scanf("%s",&username);

    printf("\nPassword : ");
    scanf("%s",&password);

    if(strcmp(admin.password,password) == 0 && strcmp(admin.username,username) == 0)
    {

        Notifiction("Welcome to the federation management page!\n\n   Please select the desired option :");
        FedrasionAccount();
        return;
    }

    readTeams('\0',username,0,0);

    if(filteredteams){
        for(int i = 0 ; i < CountLines("Teams.txt") ; i++)
            if(strcmp(filteredteam[i].password,password) == 0)
            {
                strcpy(NameTeam,username);
                Notifiction("Welcome to the club management page!\n\n   Please select the desired option :");
                ClubManagementAccount();
                return;
            }

            Notifiction("Password is wrong !");

    }else
        Notifiction("There is no account with this username !");
}
void EndSeason(){

    ReadLeagueStanding();
    SortLeagueStanding();

    readTeams('\0',SelectedTeams[0].name,0,0);
    EditTeamsInformation(SelectedTeams[0].name,0,6,"",filteredteam[0].cups + 1);

    PrintLeagueStanding();
    printf("\n\nThe Champion team is : %s\n\n",SelectedTeams[0].name);

    FILE *Tiredness = fopen("Tiredness.txt","w");
    fclose(Tiredness);

    FILE *Req = fopen("RequestLeague.txt","w");
    fclose(Req);

    FILE *LeagueStanding = fopen("LeagueStanding.txt","w");
    fclose(LeagueStanding);

    FILE *GameSchedule = fopen("GameSchedule.txt","w");
    fclose(GameSchedule);

    InfoFedrasion();
    EditFedrasionInfo(2,"none");

    back();
    Notifiction("        Return to the main!");
}
void LeagueButton(){

    InfoFedrasion();

    if(strcmp(admin.LeagueStatus,"none") == 0)
        StartLeague();

    else if(strcmp(admin.LeagueStatus,"open") == 0){

        Notifiction("    transfer window was opened !");
        EditFedrasionInfo(2,"close");

    }else if(strcmp(admin.LeagueStatus,"close") == 0){

        Notifiction("    transfer window was closed !");
        EditFedrasionInfo(2,"41");

    }else if(strcmp(admin.LeagueStatus,"1") == 0)
        StartWeekGames(1);

    else if(strcmp(admin.LeagueStatus,"2") == 0)
        StartWeekGames(2);

    else if(strcmp(admin.LeagueStatus,"3") == 0)
        StartWeekGames(3);

    else if(strcmp(admin.LeagueStatus,"41") == 0)
    {

        FILE *Req = fopen("Tiredness.txt","w");
        fclose(Req);

        if(CountLines("RequestLeague.txt") != 4)
        {
            Notifiction("    You can not start the league !\n\n     The min number of teams is 4 ");
            return;
        }

        else
            EditFedrasionInfo(2,"42");
        
        Notifiction("    You can not start the league !\n\n     The min number of teams is 4 ");
    }
    else if(strcmp(admin.LeagueStatus,"42") == 0)
        StartWeekGames(4);

    else if(strcmp(admin.LeagueStatus,"5") == 0)
        StartWeekGames(5);
    
    else if(strcmp(admin.LeagueStatus,"6") == 0)
        StartWeekGames(6);

    else if(strcmp(admin.LeagueStatus,"end") == 0)
        EndSeason();

}
void UpcomingOpponent(){

    char teams1[12][Maxline] , teams2[12][Maxline] , goals1[12][Maxline] , goals2[12][Maxline], str[Maxline] , str2[Maxline];
    int count = 0;

    FILE *GameSchedule = fopen("GameSchedule.txt","r");

    for (int i = 0; i < 12; i++)
        fscanf(GameSchedule,"%s%s%s%s",teams1[i],goals1[i],goals2[i],teams2[i]);
    
    fclose(GameSchedule); 

    for (int i = 0; i < 12; i++)
        if(strcmp(goals1[i],"-") == 0 && (strcmp(strlwr(teams1[i]),NameTeam) == 0 || strcmp(strlwr(teams2[i]),NameTeam) == 0))
        {
            printf("---------------------------------------------------------------------------------------------------------\n\n");
            printf("Next Game :\n\n%s  %s %s  %s\n\n",teams1[i],goals1[i],goals2[i],teams2[i]);

            if(strcmp(strlwr(NameTeam),strlwr(teams1[i])) == 0)
                strcpy(str2,teams2[i]);

            else
                strcpy(str2,teams1[i]);

            break;
        }

    FILE *Req = fopen("RequestLeague.txt","r");

    for (int i = 0; i < CountLines("RequestLeague.txt") ; i++)
    {
        fscanf(Req,"%s",str);
        readPlayers(0,100,0,100,10,20,'\0',"all","all","all",str,0);

        if(strcmp(strlwr(str2),strlwr(filteredPlayer[0].TeamName)) == 0)
            count ++;
    }
    
    fclose(Req);

    FILE *Reque = fopen("RequestLeague.txt","r");

    if(count == 5)
    {

        printf("---------------------------------------------------------------------------------------------------------\n\n");
        printf(" Row   Name            ID    AtPower   DefPower  value     state       foot    TeamName      post\n\n");
        printf("---------------------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < CountLines("RequestLeague.txt") ; i++)
        {
            char str1[Maxline] ;
            fscanf(Reque,"%s",str1);

            readPlayers(0,100,0,100,10,20,'\0',"all","all","all",str1,0);

            if(strcmp(strlwr(str2),strlwr(filteredPlayer[0].TeamName)) == 0){

                if(filteredPlayer[0].state[0] == 'f')
                    strcpy(str1,"Not Deprived");

                else
                    strcpy(str1,"  Deprived");

                printf("%3d    %-15s %-7d %-10d %-7d %-5d %-14s %-7s %-13s %-10s\n",i+1,filteredPlayer[0].name,filteredPlayer[0].ID,filteredPlayer[0].AttackingPower,filteredPlayer[0].DefencingPower,filteredPlayer[0].value,str1,filteredPlayer[0].foot,filteredPlayer[0].TeamName,filteredPlayer[0].post);
                printf("---------------------------------------------------------------------------------------------------------\n");
            }
        }
    }

    else
    {
        readPlayers(0,100,0,100,10,20,'\0',"all","all",NameTeam,"all",0);
        printPlayer();
    } 
}
void DepriveTeams(){
                        
    char name[Maxline] = "all";
    int ID = 0;

    printf("---------------------------------------\n\n");
    printf("Deprive by ID or name :\n\n");
    printf("1 -> name\n2 -> ID\n3 -> Back\n\nYour choice is : ");

    scanf("%s",&choice);

    if(choice[0] == '1')
    {
        printf("\nEnter name : ");
        scanf("%s",&name);
    }
    
    else if(choice[0] == '2')
    {
        printf("\nEnter ID : ");
        scanf("%d",&ID);
    }
    
    else if(choice[0] == '3')
    {
        Notifiction("         Return to the main!");
        return;
    }
    
    else
    {
        Notifiction("Invalid inputs ... \n\n        Return to the main!");
        return;
    }
    
    system("cls");
    readTeams('\0',name,ID,0);

    if(filteredteam[0].state[0] == 'f' && filteredteams)
        EditTeamsInformation(name,ID,5,"d",0);
                        
    else
        EditTeamsInformation(name,ID,5,"f",0);
}
void ExitQuistion(){

    Notifiction("        Are you want to exit ?");
    printf("1 -> Yes\n2 -> No\n\nYour choice is : ");

    char str[Maxline];
    scanf("%s",&str);

    if(str[0] == '1')
    {
        Notifiction("      Return to the Login page!");
        LoginPage();
    }

    else
    {
        Notifiction("         Return to the main!");
        return;
    }
}
void EditClubInfo(){
    
    char newInformation[Maxline],password[Maxline],password1[Maxline];

    Notifiction("What information do you want to edit?");
    printf("1 -> Edit name\n2 -> Edit password\n3 -> Edit email\n\nYour choice is : ");
    scanf("%s",&choice);

    if(choice[0] == 49)
    {
        printf("\n\nEnter name : ");
        scanf("%s",&newInformation);
        EditTeamsInformation(NameTeam,0,2,newInformation,0);
    }
    
    else if(choice[0] == 50)
    {
        Notifiction("Please enter new password :");

        printf("New Password : ");
        scanf("%s",&password);

        printf("\nRepeate Password : ");
        scanf("%s",&password1);

        if(PasswordSecurity(password))
        {
            Notifiction("           Poor password !");
            return;
        }

        if(strcmp(password,password1))
        {
            Notifiction("Password and repeat it does not match !");
            return;
        }

        else
        {
            EditTeamsInformation(NameTeam,0,4,password,0);
            Notifiction("Password is successfully changed !");
        }
    }
    
    else if(choice[0] == 51)
    {      
        printf("\n\nEnter email : ");
        scanf("%s",&newInformation);
        EditTeamsInformation(NameTeam,0,3,newInformation,0);
    }
    
    else
    {
        Notifiction("\n\nInvalid inputs ... \n\n    Return to the main!");
        return;
    }
}
void ClubManagementAccount(){

    while (1){

        printf("1 -> Buy a Player\n");
        printf("2 -> Sell a Player\n");
        RequestButtonTitle();
        printf("4 -> League Standing\n");
        printf("5 -> Fixtures\n");
        printf("6 -> Upcoming Opponent\n");
        printf("7 -> Change Information\n");
        printf("8 -> Remaining budget\n9 -> Exit\n\nYour choice is : ");

        choose() ? LoginPage() : system("cls");

        if(choice[0] == '1')
            BuyPlayer();

        else if(choice[0] == '2')
            SellPlayer();
    
        else if(choice[0] == '3')
        {
            int flag = 0;
            for(int i = 0;4 > i;i++)
                if(!strcmp(SelectedTeams[i].name,NameTeam))
                    flag = 1;

            if((strcmp(admin.LeagueStatus,"none") && flag == 0) || (strcmp(admin.LeagueStatus,"41") && flag == 0))
                SubmitSquad();
                
            else
                SelectSquad();
        }
        
        else if(choice[0] == '4')
        {
            InfoFedrasion();
            
            if(strcmp(admin.LeagueStatus,"none") == 0)
            {
                Notifiction("  The league is not currently running");
                continue;
            }

            ReadLeagueStanding();
            SortLeagueStanding();
            PrintLeagueStanding();
            back();
            Notifiction("        Return to the main!");
        }
        
        else if(choice[0] == '5')
        {

            if(strcmp(admin.LeagueStatus,"none") == 0)
            {
                Notifiction("  The league is not currently running");
                continue;
            }

            PrintGameSchedule();
            back();
            Notifiction("        Return to the main!");
        }

        else if(choice[0] == '6')
        {
            if(strcmp(admin.LeagueStatus,"none") == 0)
            {
                Notifiction("  The league is not currently running");
                continue;
            }       

            UpcomingOpponent();
            back();
            Notifiction("        Return to the main!");
        }

        else if(choice[0] == '7')
            EditClubInfo();

        else if(choice[0] == '8')
        {
            readTeams('\0',NameTeam,0,0);
            system("cls");
            printf("------------------------------------\n\n    Remaining budget : %d\n\n------------------------------------\n",filteredteam[0].money);
            back();
            Notifiction("        Return to the main!");
        }

        else if(choice[0] == '9')           
            ExitQuistion();

        else
        {
            Notifiction("Invalid inputs ... \n\n        Return to the main!");
            break;
        }
    }
}
void AddTeamButtun(){

    while (1)
    {   
        printf("---------------------------------------\n\n");
        printf("1 -> Add Team\n2 -> Back\n\nYour choice is : ");

        choose() ? LoginPage() : system("cls");

        if(choice[0] == '1')
            AddTeam();

        else if(choice[0] == '2')
        {
            Notifiction("         Return to the main!");
            break;
        }

        else
        {
            Notifiction("Invalid inputs ... \n\n        Return to the main!");
            break;
        }
    }
}
void AddPlayerButtun(){
    
    while (1)
    {   
        printf("---------------------------------------\n\n");
        printf("1 -> Add player\n2 -> Edit player\n3 -> Back\n\nYour choice is : ");

        choose() ? LoginPage() : system("cls");

        if(choice[0] == '1')
            AddPlayer();

        else if(choice[0] == '2')
            EditPlayer();
                
        else if(choice[0] == '3')
        {
            Notifiction("         Return to the main!");
            break;
        }
                
        else
        {
            Notifiction("Invalid inputs ... \n\n        Return to the main!");
            break;
        }
    }
}
void Showteams(){

    printf("---------------------------------------\n\n");
    printf("1 -> Show all teams \n");
    printf("2 -> Search by name or ID\n");
    printf("3 -> List of deprived teams\n");
    printf("4 -> Deprive or cancellation of deprivation the team\n");
    printf("5 -> Back\n\nYour choice is : ");

    choose() ? LoginPage() : system("cls");

    while (1)
    {
        if(choice[0] == '1')
        {

        readTeams('\0',"all",0,0);
        printteam();

        int ID;
        printf("\nEnter ID to show team players (Enter 0 to back) : ");

        scanf("%d",&ID);
        system("cls");

        if(ID == 0)
        { 
            Notifiction("         Return to the main!");
            break;
        }

        readTeams('\0',"all",ID,0);
        readPlayers(0,100,0,100,0,100,'\0',"all","all",filteredteam[0].name,"all",0);
        printPlayer();

        }
                
        else if(choice[0] == '2')
            SearchTeamBy();

        else if(choice[0] == '3')
        {
            readTeams('d',"all",0,0);
            printteam();
            back();
        }

        else if(choice[0] == '4')
            DepriveTeams();
                
        else
            Notifiction("Invalid inputs ... \n\n");
                    
        Notifiction("         Return to the main!");
        break;
    }
}
void ShowPlayers(){

    while (1)
    {
        Notifiction("           Show players \n\n   Please select the desired option :");
        printf("1 -> Show all users without order and category \n");
        printf("2 -> Search by name or ID\n");
        printf("3 -> Advanced search\n");
        printf("4 -> List of deprived players\n");
        printf("5 -> Deprive or cancellation of deprivation the player\n");
        printf("6 -> Back \n\nYour choice is : ");

        choose() ? LoginPage() : system("cls");

        if(choice[0] == '1')
        {
            readPlayers(0,100,0,100,0,100,'\0',"all","all","all","all",0);
            printPlayer();
            back();
        }
                
        else if(choice[0] == '2')
            SearchBy(1);

        else if(choice[0] == '3')
            AdvancedSearch(1);

        else if(choice[0] == '4')
        {
            readPlayers(0,100,0,100,0,100,'d',"all","all","all","all",0);
            printPlayer();
            back();
        }
                
        else if(choice[0] == '5')
            DeprivePlayers();

        else if(choice[0] == '6'){
            Notifiction("         Return to the main!");
            break;
        }
                
        else
        {
            Notifiction("Invalid inputs ... \n\n        Return to the main!");
            break;
        }
    }
}
void FedrasionAccount(){

    while (1)
    {
        printf("1 -> Add team\n");
        printf("2 -> Add / Edit player\n");
        printf("3 -> Show teams\n");
        printf("4 -> Show players\n");
        LeagueButtonTitle();
        printf("\n6 -> Exit\n\nYour choice is : ");

        choose() ? LoginPage() : system("cls");

        if(choice[0] == '1')
            AddTeamButtun();

        else if(choice[0] == '2')
            AddPlayerButtun();

        else if(choice[0] == '3')
            Showteams();

        else if(choice[0] == '4')
            ShowPlayers();

        else if(choice[0] == '5')
            LeagueButton();

        else if(choice[0] == '6')
            ExitQuistion();
        
        else
        {
            Notifiction("           Invalid inputs ...");
            break;   
        }
    }
}
void Forgetpassword(){

    char TeamName[Maxline],email[Maxline],password[Maxline],password1[Maxline];

    Notifiction("Please enter your Club Name and email :");
            
    printf("Club Name : ");
    scanf("%s",&TeamName);

    printf("\nEmail : ");
    scanf("%s",&email);

    readTeams('\0',TeamName,0,0);

    if(filteredteams)
    {
        if(strcmp(strlwr(filteredteam[0].name),strlwr(TeamName)) == 0 && strcmp(strlwr(filteredteam[0].email),strlwr(email)) == 0)
        {
            Notifiction("Please enter new password :");

            printf("New Password : ");
            scanf("%s",&password);

            printf("\nRepeate Password : ");
            scanf("%s",&password1);

            if(PasswordSecurity(password))
            {
                Notifiction("           Poor password !");
                return;
            }

            if(strcmp(password,password1))
            {
                Notifiction("Password and repeat it does not match !");
                return;
            }

            else
            {
                EditTeamsInformation(TeamName,0,4,password,0);
                Notifiction("Password is successfully changed !");
            }
        }

    }else
        Notifiction("There is no account with this Club Name !");
}
void LoginPage(){

    while (1){

        printf("1 -> Login\n");
        printf("2 -> Forget password\n");
        printf("3 -> Exit\n");
        printf("\nInput : ");
        
        scanf("%s",&choice);

        if(choice[0] == '1') 
            Login();

        else if(choice[0] == '2')
            Forgetpassword();
    
        else if(choice[0] == '3')
            exit(0);
        
        else
            Notifiction("Invalid inputs ... \n\n        Return to the main!");
    }
}
