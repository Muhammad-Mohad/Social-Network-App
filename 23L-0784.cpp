#include <iostream>
#include <fstream>
using namespace std;

class Object;
class Post;
class Controller;
class Page;
class User;
class Date;
class PostContent;
class Activity;
class Comment;
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
        void PrintTimeline(User*);
        void PrintTimeline(Page*);
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
        int activityCount;
        int commentCount;
        const int maxSize = 10;
        Object* sharedBy;
        Object** likedBy;
        Activity** activity;
        Comment** comment;

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
        void AddToTimeline(Activity*);
        void AddComment(Comment*);
        int GetActivityCount();
        Activity* GetActivity(int);
        int GetCommentCount();
        Comment* GetComment(int);
        void DisplayDate();
        void PostComment(Object*, const char*);
        void ViewPost(Post*);
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Controller
{
    private:
        int totalUsers;
        int totalPages;
        int totalPosts;
        int totalActivities;
        int totalComments;
        User** allUsers;
        Page** allPages;
        Post** allPosts;
        Activity** allActivities;
        Comment** allComments;

    public:
        Controller();
        ~Controller();
        User* SearchUserByID(const char*);
        Page* SearchPageByID(const char*);
        Post* SearchPostByID(const char*);
        void LoadAllUsers(ifstream&);
        void LoadAllPages(ifstream&);
        void LinkUsersAndPages(ifstream&);
        void LoadAllPosts(ifstream&);
        void LoadAllActivities(ifstream&);
        void LoadAllComments(ifstream&);
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
        void ViewHomePage();
        const char* GetID();
        const char* GetFirstName();
        const char* GetLastName();
        int GetIndex();
        Post** GetTimeline();
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
        int GetIndex();
        Post** GetTimeline();
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

class PostContent
{
    protected:
        char* postID;

    public:
        PostContent();
        virtual ~PostContent();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Activity : public PostContent
{
    friend class Controller;

    private:
        int type;
        char* value;

    public:
        Activity();
        ~Activity();
        int GetType();
        const char* GetValue();
        void DisplayActivity(int);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




class Helper
{
    public:
        static bool SubStringExists(const char*, const char*);
        static int StringLength(char*);
        static char* GetStringFromBuffer(char*);
        static void StringCopy(char*&, char*&);
        static void RemoveExtraSpaces(char*&);
        static int CompareString(const char*, const char*);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Comment
{
    friend class Controller;

    private:
        char* text;
        char* postId;
        char* objectId;
        char* commentId;
        Object* commentBy;

    public:
        Comment();
        ~Comment();
        const char* GetText();
        Object* GetCommentBy();
        void SetText(const char*);
        void SetCommentBy(Object*);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Comment::Comment()
{
    text = nullptr;
    postId = nullptr;
    objectId = nullptr;
    commentId = nullptr;
    commentBy = nullptr;
}

Comment::~Comment()
{
    delete[] text;
    delete[] objectId;
    delete[] postId;
    delete[] commentId;
}

const char* Comment::GetText()
{
    return text;
}

Object* Comment::GetCommentBy()
{
    return commentBy;
}

void Comment::SetText(const char* newText)
{
    text = const_cast<char*>(newText);
}

void Comment::SetCommentBy(Object* obj)
{
    commentBy = obj;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



Activity::Activity()
{
    type = 0;
    value = nullptr;
}

Activity::~Activity()
{
    delete[] value;
}

int Activity::GetType()
{
    return type;
}

const char* Activity::GetValue()
{
    return value;
}

void Activity::DisplayActivity(int type)
{
    switch(type)
    {
        case 1:
            cout << " is Feeling";
            break;
        case 2:
            cout << " is Thinking about";
            break;
        case 3:
            cout << " is Making";
            break;
        case 4:
            cout << " is Celebrating";
            break;
        default:
            cout << " Activity";
            break;
    }

    cout << value;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PostContent::PostContent()
{
    postID = nullptr;
}

PostContent::~PostContent()
{
    delete[] postID;
}


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


void Object::PrintTimeline(User* user)
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tView Timeline\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << user->GetFirstName() << " " << user->GetLastName() << " - Timeline\n\n";

    for(int i = 0; i < index; i++)
    {
        if(timeline[i]->GetSharedBy() == user)
        {
            cout << "--- " << user->GetFirstName() << " " << user->GetLastName();

            for (int j = 0; j < timeline[i]->GetActivityCount(); j++)
            {
                Activity* activity = timeline[i]->GetActivity(j);
                int type = activity->GetType();
                
                activity->DisplayActivity(type);
            }

            timeline[i]->DisplayDate();
            cout << "\t\"" << timeline[i]->GetContent() << "\"\n";

            for(int k = 0; k < timeline[i]->GetCommentCount(); k++) 
            {
                Comment* cmnt = timeline[i]->GetComment(k);
                cout << "\t\t" << cmnt->GetCommentBy()->GetFirstName() << " " << cmnt->GetCommentBy()->GetLastName() << ": " << "\"" << cmnt->GetText() << "\"\n";
            }

            cout << endl;
        }
    }
}

void Object::PrintTimeline(Page* page)
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tViewing Page \"" << page->GetID() << "\"\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << page->GetTitle() << endl;

    for(int i = 0; i < index; i++)
    {
        if(timeline[i]->GetSharedBy() == page)
        {
            cout << "--- " << page->GetTitle();

            for (int j = 0; j < timeline[i]->GetActivityCount(); j++)
            {
                Activity* activity = timeline[i]->GetActivity(j);
                int type = activity->GetType();
                
                activity->DisplayActivity(type);
            }

            timeline[i]->DisplayDate();
            cout << "\t\"" << timeline[i]->GetContent() << "\"\n";

            int commentCount = timeline[i]->GetCommentCount();
            if(commentCount > 0) 
            {
                for (int k = 0; k < commentCount; k++) 
                {
                    Comment* comment = timeline[i]->GetComment(k);

                    if(comment->GetCommentBy()->GetTitle() != nullptr)
                        cout << "\t\t" << comment->GetCommentBy()->GetTitle() << ": " << "\"" << comment->GetText() << "\"" << endl;

                    else
                        cout << "\t\t" << comment->GetCommentBy()->GetFirstName() << " " << comment->GetCommentBy()->GetLastName() << ": " << "\"" << comment->GetText() << "\"" << endl;
                }
                cout << endl;
            }
        }
    }
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

    for(char* temp = str; *temp != '\0'; temp++)
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

void Helper::RemoveExtraSpaces(char*& str) 
{
    if(str == nullptr) 
        return;
    
    int len = StringLength(str);
    int start = 0;
    int end = len - 1;
    
    while(start < len && str[start] == ' ') 
    {
        start++;
    }
    
    if(start == len) 
    {
        str[0] = '\0';
        return;
    }
    
    for(int i = start; i <= end; i++) 
    {
        str[i - start] = str[i];
    }
    
    str[end - start + 1] = '\0';
}

int Helper::CompareString(const char* str1, const char* str2)
{
    while(*str1 != '\0' && *str2 != '\0') 
    {
        if(*str1 > *str2) 
            return 1; 
        else if(*str1 < *str2)
            return -1;

        str1++;
        str2++;
    }
    
    if(*str1 == '\0' && *str2 == '\0') 
        return 0;

    else if(*str1 == '\0')
        return -1;

    else
        return 1;
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

    Helper::RemoveExtraSpaces(temp2);

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

int Page::GetIndex()
{
    return index;
}

Post** Page::GetTimeline()
{
    return timeline;
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

    activity = new Activity*[maxSize];

    for(int i = 0; i < maxSize; i++)
        activity[i] = nullptr;

    comment = new Comment*[maxSize];

    for(int i = 0; i < maxSize; i++)
        comment[i] = nullptr;

    day = 0;
    month = 0;
    year = 0;
    likeCount = 0;
    activityCount = 0;
    commentCount = 0;
}

Post::~Post()
{
    delete[] id;
    delete[] content;
    delete[] likedBy;
    delete[] activity;
    delete[] comment;
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
    static int count = 0;
    count++;

    if(count == 1)
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

    else if(count == 2)
    {
        cout << "\n--------------------------------------------------------------------------\n\n";
        cout << "Command:\tLikedPost \"" << id << "\"\n";
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
    
}

void Post::AddToTimeline(Activity* act)
{
    for(int i = 0; i < activityCount; i++)
        if(activity[i] == act)
            return;

    for(int i = 0; i < maxSize; i++)
    {
        if(activity[i] == nullptr)
        {
            activity[i] = act;
            activityCount++;
            return;
        }
    }

    cout << "\nTimeline is full. Cannot add more activities.\n";
}

void Post::AddComment(Comment* cmnt)
{
    for(int i = 0; i < commentCount; i++)
        if(comment[i] == cmnt)
            return;

    for(int i = 0; i < maxSize; i++)
    {
        if(comment[i] == nullptr)
        {
            comment[i] = cmnt;
            commentCount++;
            return;
        }
    }

    cout << "\nComments List is full. Cannot add more comments.\n";
}

int Post::GetActivityCount()
{
    return activityCount;
}

Activity* Post::GetActivity(int index)
{
    return activity[index];
}

int Post::GetCommentCount()
{
    return commentCount;
}

Comment* Post::GetComment(int index)
{
    return comment[index];
}

void Post::DisplayDate()
{
    if(day == Date::day && month == Date::month && year == Date::year)
        cout << " (1h)\n";
    else if(day == Date::day - 1 && month == Date::month && year == Date::year)
        cout << " (1d)\n";
    else if(day == Date::day - 2 && month == Date::month && year == Date::year)
        cout << " (2d)\n";
    else if(day == Date::day - 3 && month == Date::month && year == Date::year)
        cout << " (3d)\n";
    else
        cout << " (" << day << "/" << month << "/" << year << ")\n";
}

void Post::PostComment(Object* obj, const char* content)
{
    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tPostComment(" << id << ", " << content << ")\n";

    for(int i = 0; i < commentCount; i++)
        if(comment[i] != nullptr && Helper::CompareString(comment[i]->GetText(), content) == 0 && comment[i]->GetCommentBy() == obj)
            return;
            

    for(int i = 0; i < maxSize; i++)
    {
        if(comment[i] == nullptr)
        {
            comment[i] = new Comment;
            comment[i]->SetText(content);
            comment[i]->SetCommentBy(obj);
            commentCount++;
            return;
        }
    }

    cout << "\nComments List is full. Cannot add more comments.\n";
}

void Post::ViewPost(Post* post)
{
    cout << "Command:\tView Post" << "(" << post->GetID() << ")\n\n";
    cout << "--- " << post->GetSharedBy()->GetFirstName() << " " << post->GetSharedBy()->GetLastName();

    for (int j = 0; j < post->GetActivityCount(); j++)
    {
        Activity* activity = post->GetActivity(j);
        int type = activity->GetType();
        
        activity->DisplayActivity(type);
    }
    
    post->DisplayDate();

    cout << "\t\"" << post->GetContent() << "\"\n"; 

    for(int k = 0; k < post->GetCommentCount(); k++) 
    {
        Comment* cmnt = post->GetComment(k);
        cout << "\t\t" << cmnt->GetCommentBy()->GetFirstName() << " " << cmnt->GetCommentBy()->GetLastName() << ": " << "\"" << cmnt->GetText() << "\"\n";
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
    cout << "\nCommand:\tSet Current User \"" << id << "\"\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << fName << " " << lName << " succesfully set as Current User\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
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

void User::ViewHomePage() 
{
    int minRequiredDay = 14;
    int maxRequiredDay = 17;
    int requiredMonth = 4;
    int requiredYear = 2024;

    cout << "\n--------------------------------------------------------------------------\n\n";
    cout << "Command:\tView Home Page\n\n";
    cout << "--------------------------------------------------------------------------\n\n";
    cout << fName << " " << lName << " - Home Page\n\n";

    for(int i = 0; i < index; i++) 
    {
        Post* post = timeline[i];

        if(post->GetSharedBy() == this && post->GetDay() <= maxRequiredDay && post->GetDay() >= minRequiredDay && post->GetMonth() == requiredMonth && post->GetYear() == requiredYear) 
        {
            cout << "--- " << post->GetSharedBy()->GetFirstName() << " " << post->GetSharedBy()->GetLastName();

            for (int j = 0; j < post->GetActivityCount(); j++)
            {
                Activity* activity = post->GetActivity(j);
                int type = activity->GetType();
                
                activity->DisplayActivity(type);
            }

            post->DisplayDate();
            cout << "\t\"" << post->GetContent() << "\"" << endl;

            int commentCount = post->GetCommentCount();

            if(commentCount > 0) 
            {
                for(int k = 0; k < commentCount; k++) 
                {
                    Comment* comment = post->GetComment(k);

                    if(comment->GetCommentBy()->GetTitle() != nullptr)
                        cout << "\t\t" << comment->GetCommentBy()->GetTitle() << ": " << "\"" << comment->GetText() << "\"" << endl;
                    else
                        cout << "\t\t" << comment->GetCommentBy()->GetFirstName() << " " << comment->GetCommentBy()->GetLastName() << ": " << "\"" << comment->GetText() << "\"" << endl;
                }
            }
        }
    }

    for (int i = 0; i < friendsCount; i++) 
    {
        User* user = friendsList[i];

        for(int j = 0; j < user->GetIndex(); j++)
        {
            Post* post = user->GetTimeline()[j];

            if(post->GetSharedBy() == user && post->GetDay() <= maxRequiredDay && post->GetDay() >= minRequiredDay && post->GetMonth() == requiredMonth && post->GetYear() == requiredYear)
            {
                cout << "\n--- " << user->GetFirstName() << " " << user->GetLastName();

                for(int j = 0; j < post->GetActivityCount(); j++)
                {
                    Activity* activity = post->GetActivity(j);
                    int type = activity->GetType();
                    
                    activity->DisplayActivity(type);
                }

            post->DisplayDate();
            cout << "\t\"" << post->GetContent() << "\"" << endl;

                int commentCount = post->GetCommentCount();

                if(commentCount > 0) 
                {
                    for(int k = 0; k < commentCount; k++)
                    {
                        Comment* comment = post->GetComment(k);

                        if(comment->GetCommentBy()->GetTitle() != nullptr)
                            cout << "\t\t" << comment->GetCommentBy()->GetTitle() << ": " << "\"" << comment->GetText() << "\"" << endl;
                        else
                            cout << "\t\t" << comment->GetCommentBy()->GetFirstName() << " " << comment->GetCommentBy()->GetLastName() << ": " << "\"" << comment->GetText() << "\"" << endl;
                    }
                }
            }
        }
    }

    for(int i = 0; i < likedPagesCount; i++) 
    {
        Page* page = likedPages[i];

        for(int j = 0; j < page->GetIndex(); j++) 
        {
            Post* post = page->GetTimeline()[j];

            if(post->GetSharedBy() == page && post->GetDay() <= maxRequiredDay && post->GetDay() >= minRequiredDay && post->GetMonth() == requiredMonth && post->GetYear() == requiredYear)
            {
                cout << "\n--- " << page->GetTitle();

                for (int j = 0; j < post->GetActivityCount(); j++)
                {
                    Activity* activity = post->GetActivity(j);
                    int type = activity->GetType();
                    
                    activity->DisplayActivity(type);
                }

            post->DisplayDate();
            cout << "\t\"" << post->GetContent() << "\"" << endl;

                int commentCount = post->GetCommentCount();

                if(commentCount > 0)
                {
                    for (int k = 0; k < commentCount; k++)
                    {
                        Comment* comment = post->GetComment(k);

                        if(comment->GetCommentBy()->GetTitle() != nullptr)
                            cout << "\t\t" << comment->GetCommentBy()->GetTitle() << ": " << "\"" << comment->GetText() << "\"" << endl;
                        else
                            cout << "\t\t" << comment->GetCommentBy()->GetFirstName() << " " << comment->GetCommentBy()->GetLastName() << ": " << "\"" << comment->GetText() << "\"" << endl;
                    }
                }
            }
        }
    }
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

int User::GetIndex()
{
    return index;
}

Post** User::GetTimeline()
{
    return timeline;
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
    totalComments = 0;
    allUsers = nullptr;
    allPages = nullptr;
    allPosts = nullptr;
    allActivities = nullptr;
    allComments = nullptr;
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

    if(allActivities != nullptr)
    {
        for(int i = 0; i < totalActivities; i++)
            delete allActivities[i];
    }

    delete[] allActivities;

    if(allComments != nullptr)
    {
        for(int i = 0; i < totalComments; i++)
            delete allComments[i];
    }

    delete[] allComments;
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

void Controller::LoadAllActivities(ifstream& inputFile)
{
    inputFile >> totalActivities;

    allActivities = new Activity*[totalActivities];

    for(int i = 0; i < totalActivities; i++)
    {
        allActivities[i] = new Activity;
        
        const int idSize = 7;
        const int valueSize = 30;

        char* temp1 = new char[idSize];
        char* temp2 = new char[valueSize];

        inputFile >> temp1;

        allActivities[i]->postID = Helper::GetStringFromBuffer(temp1);

        Post* ptr = SearchPostByID(allActivities[i]->postID);

        if(ptr)
            ptr->AddToTimeline(allActivities[i]);

        inputFile >> allActivities[i]->type;

        inputFile.getline(temp2, valueSize - 1);

        allActivities[i]->value = Helper::GetStringFromBuffer(temp2);

        delete[] temp1;
        delete[] temp2;
    }
}

void Controller::LoadAllComments(ifstream& inputFile)
{
    inputFile >> totalComments;

    allComments = new Comment*[totalComments];

    for(int i = 0; i < totalComments; i++)
    {
        allComments[i] = new Comment;

        const int IdSize = 4;
        const int postIdSize = 7;
        const int textSize = 80;

        char* temp1 = new char[IdSize];
        char* temp2 = new char[postIdSize];
        char* temp3 = new char[IdSize];
        char* temp4 = new char[textSize];

        inputFile >> temp1;

        allComments[i]->commentId = Helper::GetStringFromBuffer(temp1);

        inputFile >> temp2;

        allComments[i]->postId = Helper::GetStringFromBuffer(temp2);

        Post* ptr = SearchPostByID(allComments[i]->postId);

        if(ptr)
            ptr->AddComment(allComments[i]);

        inputFile >> temp3;

        allComments[i]->objectId = Helper::GetStringFromBuffer(temp3);

        Object* obj = SearchUserByID(allComments[i]->objectId);

        if(!obj)
            obj = SearchPageByID(allComments[i]->objectId);

        allComments[i]->commentBy = obj;

        inputFile.getline(temp4, textSize - 1);

        Helper::RemoveExtraSpaces(temp4);

        allComments[i]->text = Helper::GetStringFromBuffer(temp4);

        delete[] temp1;
        delete[] temp2;
        delete[] temp3;
        delete[] temp4;
    }
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

Post* Controller::SearchPostByID(const char* id)
{
    for(int i = 0; i < totalPosts; i++)
    {
        if(Helper::SubStringExists(allPosts[i]->GetID(), id))
            return allPosts[i];
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

    post->SetLikedBy(user);

    post->PrintLikedBy(user);

    int currentPage = 0;
    Page* page = allPages[currentPage];

    page->PrintTimeline(page);

    user->ViewHomePage();

    int viewPost1 = 3;
    Post* post2 = allPosts[viewPost1];

    post2->PostComment(user, "Good Luck for your Result");
    post2->ViewPost(post2);

    int viewPost2 = 7;
    Post* post3 = allPosts[viewPost2];

    post3->PostComment(user, "Thanks for the wishes");
    post3->ViewPost(post3);
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
    LoadAllActivities(inputFile5);
    LoadAllComments(inputFile6);

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