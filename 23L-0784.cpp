#include <iostream>
#include <fstream>
using namespace std;

class Object;
class Post;
class Controller;
class Page;
class User;
class Date;
class Helper;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class Object
{
    private:
        char* id;
        const int maxSize = 10;

    protected:
        int index;
        Post** timeline;

    public:
        Object();
        ~Object();
        virtual const char* GetID();
        virtual const char* GetTitle();
        virtual const char* GetFirstName();
        virtual const char* GetLastName();
        void AddToTimeline(Post*);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




class Post
{
    private:
        char* id;
        char* content;
        int day;
        int month;
        int year;
        int likeCount;
        const int maxSize = 10;
        Object* sharedBy;
        Object** likedBy;

    public:
        Post();
        ~Post();
        void ReadDataFromFile(ifstream&);
        void SetSharedBy(Object*);
        void SetLikedBy(Object*);
        int GetDay();
        int GetMonth();
        int GetYear();
        const char* GetID();
        const char* GetContent();
        void PrintLikedBy(Object*);
        Object* GetSharedBy();
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Controller
{
    private:
        int totalUsers;
        int totalPages;
        int totalPosts;
        int totalActivities;
        User** allUsers;
        Page** allPages;
        Post** allPosts;

    public:
        Controller();
        ~Controller();
        User* SearchUserByID(const char*);
        Page* SearchPageByID(const char*);
        void LoadAllUsers(ifstream&);
        void LoadAllPages(ifstream&);
        void LinkUsersAndPages(ifstream&);
        void LoadAllPosts(ifstream&);
        void LoadData();
        void Run();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class User : public Object
{
    private:
        char* id;
        char* fName;
        char* lName;
        int friendsCount;
        int likedPagesCount;
        const int maximumFriends = 10;
        const int maximumLikedPages = 10;
        User** friendsList;
        Page** likedPages;

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
        void PrintTimeline(User*);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Page : public Object
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
        void PrintTimeline(Page*);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Date
{
    public:
        static const int day = 17;
        static const int month = 4;
        static const int year = 2024;
        static void CurrentDate();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



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




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Object::Object()
{
    id = nullptr;

    timeline = new Post*[maxSize];

    for(int i = 0; i < maxSize; i++)
        timeline[i] = nullptr;

    index = 0;
}

Object::~Object()
{
    delete[] id;
    delete[] timeline;
}


void Object::AddToTimeline(Post* post)
{
    for(int i = 0; i < index; i++)
        if(timeline[i] == post)
            return;

    for(int i = 0; i < maxSize; i++)
    {
        if(timeline[i] == nullptr)
        {
            timeline[i] = post;
            index++;
            return;
        }
    }    
    
    cout << "\nTimeline is full. Cannot add more posts.\n";
}


const char* Object::GetID()
{
    return id;
}

const char* Object::GetFirstName()
{
    return nullptr;
}

const char* Object::GetLastName()
{
    return nullptr;
}

const char* Object::GetTitle()
{
    return nullptr;
}

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
    char* temp1 = new char[idSize];

    inputFile >> temp1;
    id = Helper::GetStringFromBuffer(temp1);

    const int titleSize = 50;
    char* temp2 = new char[titleSize];

    inputFile.getline(temp2, titleSize - 1);

    title = Helper::GetStringFromBuffer(temp2);

    delete[] temp1;
    delete[] temp2;
}

const char* Page::GetID()
{
    return id;
}

const char* Page::GetTitle()
{
    return title;
}

void Page::PrintTimeline(Page* page)
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tViewing Page \"" << id << "\"\n\n";
    cout << title << endl;

    for(int i = 0; i < index; i++)
    {
        if(timeline[i]->GetSharedBy() == page)
        {
            cout << "---" << title << " (" << timeline[i]->GetDay() << "/" << timeline[i]->GetMonth() << "/" << timeline[i]->GetYear() << "):\n";
            cout << "\t\"" << timeline[i]->GetContent() << "\"\n\n";
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Post::Post()
{
    id = nullptr;
    content = nullptr;
    sharedBy = nullptr;

    likedBy = new Object*[maxSize];

    for(int i = 0; i < maxSize; i++)
        likedBy[i] = nullptr;

    day = 0;
    month = 0;
    year = 0;
    likeCount = 0;
}

Post::~Post()
{
    delete[] id;
    delete[] content;
    delete[] likedBy;
}

void Post::ReadDataFromFile(ifstream& inputFile)
{
    const int idSize = 7;
    char* temp1 = new char[idSize];

    inputFile >> temp1;
    id = Helper::GetStringFromBuffer(temp1);

    inputFile >> day >> month >> year;

    const int contentSize = 80;
    char* temp2 = new char[contentSize];
    
    inputFile.ignore(99, '\n');
    
    inputFile.getline(temp2, contentSize - 1);
    content = Helper::GetStringFromBuffer(temp2);

    delete[] temp1;
    delete[] temp2;
}

void Post::SetSharedBy(Object* obj)
{
    sharedBy = obj;
}

void Post::SetLikedBy(Object* obj)
{
    likedBy[likeCount] = obj;
    likeCount++;
}

int Post::GetDay()
{
    return day;
}

int Post::GetMonth()
{
    return month;
}

int Post::GetYear()
{
    return year;
}

const char* Post::GetID()
{
    return id;
}

const char* Post::GetContent()
{
    return content;
}

Object* Post::GetSharedBy()
{
    return sharedBy;
}

void Post::PrintLikedBy(Object* obj)
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tViewing Liked List of \"" << id << "\"\n\n";
    cout << "Post Liked By:\n";

    for(int i = 0; i < likeCount; i++)
    {
        if(likedBy[i]->GetTitle() != nullptr)
            cout << likedBy[i]->GetID() << " -" << likedBy[i]->GetTitle() << endl;
        
        else
            cout << likedBy[i]->GetID() << " - " << likedBy[i]->GetFirstName() << " " << likedBy[i]->GetLastName() << endl;
    }
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
    for(int i = 0; i < maximumFriends; i++)
        friendsList[i] = nullptr;

    likedPages = new Page*[maximumLikedPages];
    for(int i = 0; i < maximumLikedPages; i++)
        likedPages[i] = nullptr;

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
    char* temp1 = new char[idSize];

    inputFile >> temp1;
    id = Helper::GetStringFromBuffer(temp1);

    const int nameSize = 15;
    char* temp2 = new char[nameSize];

    inputFile >> temp2;
    fName = Helper::GetStringFromBuffer(temp2);

    inputFile >> temp2;
    lName = Helper::GetStringFromBuffer(temp2);

    delete[] temp1;
    delete[] temp2;
}


void User::AddFriend(User*& friendUser)
{
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
    cout << "\nCommand:\tSet Current User \"" << id << "\"\n";
    cout << fName << " " << lName << " succesfully set as Current User\n\n";
    cout << "Command:\tView Friend List\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << fName << " " << lName << " - Friend List\n\n";

    for(int i = 0; i < friendsCount; i++)
        cout << friendsList[i]->GetID() << " - " << friendsList[i]->GetFirstName() << " " << friendsList[i]->GetLastName() << endl;
}

void User::ViewLikedPages()
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tView Liked Pages\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << fName << " " << lName << " - Liked Pages\n\n";

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

void User::PrintTimeline(User* user)
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tView Timeline\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << fName << " " << lName << " - Timeline\n\n";

    for(int i = 0; i < index; i++)
    {
        if(timeline[i]->GetSharedBy() == user)
        {
            cout << "--- " << fName << " " << lName << " (" << timeline[i]->GetDay() << "/" << timeline[i]->GetMonth() << "/" << timeline[i]->GetYear() << "):\n";
            cout << "\t\"" << timeline[i]->GetContent() << "\"\n\n";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Date::CurrentDate()
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tSet Current System Date " << "\"" << day << "-" << month << "-" << year << "\"" << "\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << "System Date:\t" << day << "/" << month << "/" << year << "\n\n";
    cout << "--------------------------------------------------------------------------\n";
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Controller::Controller()
{
    totalUsers = 0;
    totalPages = 0;
    totalPosts = 0;
    totalActivities = 0;
    allUsers = nullptr;
    allPages = nullptr;
    allPosts = nullptr;
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

    if(allPosts != nullptr)
    {
        for(int i = 0; i < totalPosts; i++)
            delete allPosts[i];
    }

    delete[] allPosts;
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


void Controller::LoadAllPosts(ifstream& inputFile)
{
    inputFile >> totalPosts;

    allPosts = new Post*[totalPosts];

    for(int i = 0; i < totalPosts; i++)
    {
        allPosts[i] = new Post;
        allPosts[i]->ReadDataFromFile(inputFile);

        const char idSize = 4;
        char* temp1 = new char[idSize];

        inputFile >> temp1;

        Object* ptr = SearchUserByID(temp1);

        if(!ptr)
            ptr = SearchPageByID(temp1);

        allPosts[i]->SetSharedBy(ptr);
        ptr->AddToTimeline(allPosts[i]);

        char* temp2 = new char[idSize];

        while(true)
        {
            inputFile >> temp2;

            if(temp2[0] == '-' && temp2[1] == '1')
                break;

            Object* ptr = SearchUserByID(temp2);

            if(!ptr)
                ptr = SearchPageByID(temp2);

            allPosts[i]->SetLikedBy(ptr);
            ptr->AddToTimeline(allPosts[i]);
        }   

        delete[] temp1;
        delete[] temp2;     
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

void Controller::Run()
{
    Date::CurrentDate();
    
    int currentUser = 6;
    User* user = allUsers[currentUser];

    user->ViewFriendsList();    

    user->ViewLikedPages();
    
    user->PrintTimeline(user);

    int currentPost = 4;
    Post* post = allPosts[currentPost];

    post->PrintLikedBy(user);

    int currentPage = 0;
    Page* page = allPages[currentPage];

    page->PrintTimeline(page);
}


void Controller::LoadData()
{
    ifstream inputFile1("SocialNetworkUsers.txt");
    ifstream inputFile2("SocialNetworkPages.txt");
    ifstream inputFile3("UsersFriendsAndLikedPages.txt");
    ifstream inputFile4("SocialNetworkPosts.txt");
    ifstream inputFile5("SocialNetworkActivities.txt");
    ifstream inputFile6("SocialNetworkComments.txt");

    LoadAllUsers(inputFile1);
    LoadAllPages(inputFile2);
    LinkUsersAndPages(inputFile3);
    LoadAllPosts(inputFile4);

    inputFile1.close();
    inputFile2.close();
    inputFile3.close();
    inputFile4.close();
    inputFile5.close();
    inputFile6.close();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    Controller mainApp;
    mainApp.LoadData();
    mainApp.Run();

    return 0;
}