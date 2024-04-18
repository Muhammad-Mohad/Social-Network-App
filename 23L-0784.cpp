#include <iostream>
#include <fstream>
using namespace std;

class Page
{
    private:
        char* id;
        char* title;
    
    public:
        Page();
        ~Page();
        void ReadDataFromFile(ifstream&);
        const char* GetID();
        const char* GetTitle();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class User
{
    private:
        char* id;
        char* fName;
        char* lName;
        User** friendsList;
        Page** likedPages;
        int friendsCount;
        int likedPagesCount;
        const int maximumFriends = 10;
        const int maximumLikedPages = 10;

    public:
        User();
        ~User();
        void ReadDataFromFile(ifstream&);
        void AddFriend(User*&);
        void LikePage(Page*&);
        void ViewLikedPages();
        void ViewFriendsList();
        const char* GetID();
        const char* GetFirstName();
        const char* GetLastName();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Helper
{
    public:
        static bool SubStringExists(const char*, const char*);
        static int StringLength(char*);
        static char* GetStringFromBuffer(char*);
        static void StringCopy(char*&, char*&);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Controller
{
    private:
        User** allUsers;
        Page** allPages;
        int totalUsers;
        int totalPages;

    public:
        Controller();
        ~Controller();
        User* SearchUserByID(const char*);
        Page* SearchPageByID(const char*);
        void LoadAllUsers(ifstream&);
        void LoadAllPages(ifstream&);
        void LinkUsersAndPages(ifstream&);
        void LoadData();
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Helper::SubStringExists(const char* str, const char* subStr)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        int j = 0;

        while (subStr[j] != '\0' && str[i + j] != '\0' && str[i + j] == subStr[j])
            j++;

        if (subStr[j] == '\0')
            return true;
    }

    return false;
}

int Helper::StringLength(char* str)
{
    int stringLen = 0;
    for (char* temp = str; *temp != '\0'; temp++)
        stringLen++;

    return stringLen;
}

char* Helper::GetStringFromBuffer(char* buffer)
{
    int strLen = StringLength(buffer);
    char* str = nullptr;

    if (strLen > 0)
    {
        str = new char[strLen + 1];
        StringCopy(str, buffer);
    }
    return str;
}

void Helper::StringCopy(char*& dest, char*& src)
{
    char* tempDest = dest;

    for (char* tempSrc = src; *tempSrc != '\0'; tempSrc++, tempDest++)
        *tempDest = *tempSrc;

    *tempDest = '\0';
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



Page::Page()
{
    id = nullptr;
    title = nullptr;
}

Page::~Page()
{
    delete[] id;
    delete[] title;
}


void Page::ReadDataFromFile(ifstream& inputFile)
{
    const int idSize = 4;
    char temp1[idSize];

    inputFile >> temp1;
    id = Helper::GetStringFromBuffer(temp1);

    const int titleSize = 50;
    char temp2[titleSize];

    inputFile.getline(temp2, titleSize - 1);

    title = Helper::GetStringFromBuffer(temp2);
}

const char* Page::GetID()
{
    return id;
}

const char* Page::GetTitle()
{
    return title;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




User::User()
{
    id = nullptr;
    fName = nullptr;
    lName = nullptr;
    friendsList = nullptr;
    likedPages = nullptr;
    friendsList = new User*[maximumFriends];
    likedPages = new Page*[maximumLikedPages];
    friendsCount = 0;
    likedPagesCount = 0;
}

User::~User()
{
    delete[] id;
    delete[] fName;
    delete[] lName;
    delete[] friendsList;
    delete[] likedPages;
}


void User::ReadDataFromFile(ifstream& inputFile)
{
    const int idSize = 4;
    char temp1[idSize];

    inputFile >> temp1;
    id = Helper::GetStringFromBuffer(temp1);

    const int nameSize = 15;
    char temp2[nameSize];

    inputFile >> temp2;
    fName = Helper::GetStringFromBuffer(temp2);

    inputFile >> temp2;
    lName = Helper::GetStringFromBuffer(temp2);
}


void User::AddFriend(User*& friendUser)
{
    if(friendsList == nullptr)
        friendsList = new User*[maximumFriends];

    if(friendsCount < maximumFriends)
    {
        friendsList[friendsCount] = friendUser;
        friendsCount++;
    }
    else
        cout << "\n\nCannot add more friends.Maximum limit reached.\n\n";
}

void User::LikePage(Page*& page)
{
    if(likedPages == nullptr)
        likedPages = new Page*[maximumLikedPages];

    if(likedPagesCount < maximumLikedPages)
    {
        likedPages[likedPagesCount] = page;
        likedPagesCount++;
    }
    else
        cout << "\n\nCannot like more pages.Maximum limit reached.\n\n";
}

void User::ViewFriendsList()
{
    for(int i = 0; i < friendsCount; i++)
        cout << friendsList[i]->GetID() << " - " << friendsList[i]->GetFirstName() << " " << friendsList[i]->GetLastName() << endl;
}

void User::ViewLikedPages()
{
    for(int i = 0; i < likedPagesCount; i++)
        cout << likedPages[i]->GetID() << " - " << likedPages[i]->GetTitle() << endl;
}


const char* User::GetID()
{
    return id;
}

const char* User::GetFirstName()
{
    return fName;
}

const char* User::GetLastName()
{
    return lName;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Controller::Controller()
{
    totalUsers = 0;
    totalPages = 0;
    allUsers = nullptr;
    allPages = nullptr;
}

Controller::~Controller()
{
    if(allUsers != nullptr)
    {
        for(int i = 0; i < totalUsers; i++)
            delete allUsers[i];
    }

    delete[] allUsers;

    if(allPages != nullptr)
    {
        for(int i = 0; i < totalPages; i++)
            delete allPages[i];
    }

    delete[] allPages;
}

void Controller::LoadAllUsers(ifstream& inputFile)
{
    inputFile >> totalUsers;

    allUsers = new User*[totalUsers];

    for(int i = 0; i < totalUsers; i++)
    {
        allUsers[i] = new User;
        allUsers[i]->ReadDataFromFile(inputFile);
    }
}

void Controller::LoadAllPages(ifstream& inputFile)
{
    inputFile >> totalPages;

    allPages = new Page*[totalPages];

    for(int i = 0; i < totalPages; i++)
    {
        allPages[i] = new Page;
        allPages[i]->ReadDataFromFile(inputFile);
    }
}

void Controller::LinkUsersAndPages(ifstream& inputFile)
{
    const int maxSize = 4;

    char* userID = new char[maxSize];
    char* temp = new char[maxSize];

    while(inputFile >> userID)
    {
        if(userID[0] == '-' && userID[1] == '1')
            break;

        User* user = SearchUserByID(userID);

        while(inputFile >> temp)
        {
            if(temp[0] == '-' && temp[1] == '1')
                break;

            User* friendUser = SearchUserByID(temp);

            if(user && friendUser)
                user->AddFriend(friendUser);
        }

        while(inputFile >> temp)
        {
            if(temp[0] == '-' && temp[1] == '1')
                break;

            Page* page = SearchPageByID(temp);

            if(user && page)
                user->LikePage(page);
        }

    }

    delete[] userID;
    delete[] temp;
}

User* Controller::SearchUserByID(const char* id)
{
    for(int i = 0; i < totalUsers; i++)
    {
        if(Helper::SubStringExists(allUsers[i]->GetID(), id))
            return allUsers[i];
    }
    return nullptr;
}

Page* Controller::SearchPageByID(const char* id)
{
    for(int i = 0; i < totalPages; i++)
    {
        if(Helper::SubStringExists(allPages[i]->GetID(), id))
            return allPages[i];
    }

    return nullptr;
}


void Controller::LoadData()
{
    ifstream inputFile1("SocialNetworkUsers.txt");
    ifstream inputFile2("SocialNetworkPages.txt");
    ifstream inputFile3("UsersFriendsAndLikedPages.txt");

    LoadAllUsers(inputFile1);
    LoadAllPages(inputFile2);
    LinkUsersAndPages(inputFile3);

    int currentUser = 6;

    cout << "\nCommand:\tSet Current User \"" << allUsers[currentUser]->GetID() << "\"\n";
    cout << allUsers[currentUser]->GetFirstName() << " " << allUsers[currentUser]->GetLastName() << " succesfully set as Current User\n\n";
    cout << "Command:\tView Friend List\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << allUsers[currentUser]->GetFirstName() << " " << allUsers[currentUser]->GetLastName() << " - Friend List\n\n";

    allUsers[currentUser]->ViewFriendsList();    

    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tView Liked Pages\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << allUsers[currentUser]->GetFirstName() << " " << allUsers[currentUser]->GetLastName() << " - Liked Pages\n\n";

    allUsers[currentUser]->ViewLikedPages();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    Controller mainApp;
    mainApp.LoadData();

    return 0;
}