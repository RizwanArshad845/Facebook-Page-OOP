#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class Page;
class User;
class Object;
class Date;
class Post;
class controller;
class Activity;
class Memory;
class Comment;
class Helper {
public:
    static char* StringConcatenateWithoutSpace(const char* str1, char* str2)
    {
        int i = 0;
        while (str1[i] != '\0')
        {
            i++;
        }
        while (str2[i] != '\0')
        {
            i++;
        }

        char* str3 = new char[i + 1];
        int j = 0;
        while (str1[j] != '\0')
        {
            str3[j] = str1[j];
            j++;
        }
        i = 0;
        while (str2[i] != '\0')
        {
            str3[j] = str2[i];
            i++; j++;
        }

        str3[j] = '\0';
        return str3;
    }
    static int StringLenght(const char* str)
    {
        int i = 0;
        while (str[i] != '\0')
        {
            i++;
        }
        return i;
    }
    static void StringCopy(char*& dest, const char* src)
    {
        int i = 0;
        while (src[i] != '\0')
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }
    static char* GetStringFromBuffer(char* str)
    {
        int size_of_string = StringLenght(str);
        char* string = new char[size_of_string + 1];    // +1 for null character
        StringCopy(string, str);
        return string;
    }
    static char* GetStringFromBuffer2(const char* str2)
    {
        int size_of_string = StringLenght(str2);
        char* string = new char[size_of_string + 1];    // +1 for null character
        StringCopy(string, str2);
        return string;

    }
    static int CompareString(char* str1, const char* str2)
    {
        int i = 0;
        int j = 0;
        while (str1[i] != '\0' && str2[j] != '\0')
        {
            if (str1[i] < str2[j])
            {
                return -1;
            }

            if (str1[i] > str2[j])
            {
                return 1;
            }
            i++;
            j++;
        }
        if (str1[i] != '\0')
            return 1;
        if (str2[j] != '\0')
            return -1;
        return 0;    // out of loop will mean that both strings are equal
    }

    static char* StringConcatenate(char* str1, char* str2)
    {
        int i = 0;
        while (str1[i] != '\0')
        {
            i++;
        }
        i++;
        while (str2[i] != '\0')
        {
            i++;
        }

        char* str3 = new char[i + 1];
        int j = 0;
        while (str1[j] != '\0')
        {
            str3[j] = str1[j];
            j++;
        }
        str3[j] = ' ';
        j++;
        i = 0;
        while (str2[i] != '\0')
        {
            str3[j] = str2[i];
            i++; j++;
        }

        str3[j] = '\0';
        return str3;

    }
};
class Object {
private:
    char* id;
    int no_of_post;
protected:
    Post** Timeline;
public:
    Object() {
        id = 0;
        no_of_post = 0;
        Timeline = new Post * [10]();
    }
    virtual ~Object()     // destructor
    {
        if (id)
        {
            delete[] id;
        }
        if (Timeline)
        {
            for (int i = 0; i < 10; i++)
            {
                delete[] Timeline[i];
            }
            delete[] Timeline;
        }
    }
    virtual char* GetFullName() = 0;          // pure virtual

    virtual void PrintListView() = 0;

    char* GetID()
    {
        return id;
    }

    void PrintID()
    {
        cout << id;
    }

    virtual void ViewTimeline() = 0;

    void AddPostToTimeline(Post* ptr)
    {
        for (int i = 0; i < 10; i++)
        {
            if (Timeline[i] == 0)      // pointing to null
            {
                Timeline[i] = ptr;
                break;
            }
        }
    }
};
class Date
{
private:
    int day, month, year;
public:

    static Date currdate;
    static void SetCurrDate(int d, int m, int y)
    {
        currdate.day = d;
        currdate.month = m;
        currdate.year = y;
    }
    static Date GetCurrDate()
    {
        return currdate;
    }

    bool MemoryCheck(Date rhs)
    {
        if (day == rhs.day && month == rhs.month)
            return true;
        else
            return false;
    }

    int diffofyear(Date rhs)
    {
        int diff = currdate.year - year;
        return diff;
    }

    static Date prevdate()
    {
        Date yesterday(1, 1, 1);
        yesterday.day = currdate.day - 1;
        yesterday.month = currdate.month;
        yesterday.year = currdate.year;
        return yesterday;
    }

    Date(int d = 0, int m = 0, int y = 0)     //  overloaded default constructor
    {
        day = d;
        month = m;
        year = y;
    }

    void Print()
    {
        cout << day << "/" << month << "/" << year;
    }

    void SetDay(int d)
    {
        day = d;
    }

    void SetMonth(int m)
    {
        month = m;
    }

    void SetYear(int y)
    {
        year = y;
    }

    int GetDay()
    {
        return day;
    }

    int GetMonth()
    {
        return month;
    }

    int CompareDate(Date d)
    {
        if (year > d.year)
            return 1;

        if (year < d.year)
            return -1;

        if (year == year)
        {
            if (month > d.month)
                return 1;
            if (month < d.month)
                return -1;
            if (month == d.month)
            {
                if (day > d.day)
                    return 1;
                if (day < d.day)
                    return -1;
                if (day == day)
                    return 0;
            }
        }
    }

    int GetYear()
    {
        return year;
    }

    Date Increment_Month()
    {
        return Date(day, month + 1, year);
    }

    void ReadDataFromFile(ifstream& fin)
    {
        fin >> day;
        fin >> month;
        fin >> year;
    }

    ~Date()
    {
    }
};

Date Date::currdate = Date(1, 1, 1);
class PostContent
{
public:
    virtual void Print() {};
};
class Activity :public PostContent
{
private:
    int type;
    char* value;
public:
    Activity() {
        type = 0;
        value = nullptr;
    }
    ~Activity() {
        if (value) {
            delete[]value;
        }
    }
    void Print() {
        if (type == 1) {
            cout << "is feeling" << " " << value << endl;
        }
        else if (type == 2) {
            cout << "is thinking about" << value << endl;
        }
        else if (type == 3) {
            cout << "is Making" << value << endl;
        }
        else if (type == 4) {
            cout << "is celebrating" << value << endl;
        }
    }
    void SetActivity(int set, char* store) {
        type = set;
        value = Helper::GetStringFromBuffer(store);
    }
};
class Comment {
private:
    char* commentID;
    Object* CommentBy;
    char* commenttext;
    char* postId;
public:
    static int comment_count;
    Comment() {
        commentID = nullptr;
        CommentBy = nullptr;
        commenttext = nullptr;
        postId = 0;
        comment_count++;
    }
    ~Comment() {//destructor
        if (commentID)
        {
            delete commentID;
        }
        if (postId)
        {
            delete[] postId;
        }
        if (commenttext)
        {
            delete[] commenttext;
        }
        /*	if (commented_by)
            {
                delete[] commented_by;
            }*/

    }
    void SetValues(char* set1, Object* ptr, char* set2, char* set3) {
        commentID = Helper::GetStringFromBuffer(set1);
        CommentBy = ptr;
        commenttext = Helper::GetStringFromBuffer(set2);
        postId = Helper::GetStringFromBuffer(set3);
    }
    void Print()
    {
        cout << '\t';
        cout << CommentBy->GetFullName() << " ";
        cout << "\"" << commenttext << " \"" << endl;
    }
};
int Comment::comment_count = 0;//static initialization
class Post
{
private:
    char* post_id;
    char* text;
    Object* Shared_By;
    Date Shared_date;
    Object** Likedby;
    Comment** comments;
    PostContent* content;
public:
    Post() {
        post_id = nullptr;
        text = nullptr;
        Shared_By = nullptr;
        Shared_date = 0;
        /* Likedby = new Object * [10]();*/
        Likedby = new Object * [10];     // max 10 users an like the post
        for (int i = 0; i < 10; i++)
        {
            Likedby[i] = 0;
        }
        comments = new Comment * [12];
        for (int i = 0; i < 12; i++) {
            comments[i] = 0;
        }
        content = 0;
    }
    Post(const char* id, const char* text1, Object* postedby)
    {
        post_id = Helper::GetStringFromBuffer2(id);
        text = Helper::GetStringFromBuffer2(text1);
        Shared_date = Date::GetCurrDate();
        Shared_By = postedby;
        Likedby = 0;
        comments = 0;// max 10 users can like the post
        content = 0;
    }

    virtual ~Post() {//Virtual so the memory destructor can be called
        if (post_id)
        {
            delete[] post_id;
        }
        if (text)
        {
            delete[] text;
        }
        if (Shared_By) {
            delete[]Shared_By;
        }
        if (Likedby)
        {
            delete[] Likedby;
        }
        if (content) {
            delete[]content;
        }
        if (comments)
        {
            for (int i = 0; comments[i] != 0; i++)
            {
                if (comments[i])
                    delete comments[i];
            }
            delete[] comments;
        }
    }
    Date GetSharedDate() {
        return Shared_date;
    }
    Object* GetSharedby() {
        return Shared_By;
    }
    char* GetText() {
        return text;
    }
    void AddContent(PostContent* ptr) {
        content = ptr;
    }
    void PostComment(Post* post, Object* CommentedBy, char* text)//Adding post comment
    {
        char* id = 0;
        Comment* comment = new Comment;
        for (int i = 0; i < 10; i++)
        {
            char str[10];
            sprintf_s(str, "%d", Comment::comment_count);
            char* temp = new char[10];
            temp = Helper::StringConcatenateWithoutSpace("c", str);
            id = Helper::GetStringFromBuffer(temp);
            break;
        }
        comment->SetValues(id, CommentedBy, text, post->GetPostID());
        post->AddComment(comment);
    }
    void ViewRecent()
    {
        if (Shared_date.CompareDate(Date::GetCurrDate()) == 0 || Shared_date.CompareDate(Date::prevdate()) == 0)
        {
            PrintPost(false);
        }
    }
    void ViewOldestPost()
    {
        if (Shared_date.MemoryCheck(Date::GetCurrDate()) == 1)
        {
            cout << "On this day :\n";
            int a = Shared_date.diffofyear(Date::GetCurrDate());
            cout << a << " years ago\n";
            PrintPost();
        }
    }
    void SetLikedBy(Object* ptr)
    {
        for (int i = 0; i < 10; i++)
        {
            if (Likedby[i] == 0)
            {
                Likedby[i] = ptr;
                break;

            }
        }
    }
    void SetSharedBy(Object* person)
    {
        Shared_By = person;
    }
    void ReadDatafromFilePosts(ifstream& fin) {
        char buffer[100];
        fin >> buffer;
        post_id = Helper::GetStringFromBuffer(buffer);
        Shared_date.ReadDataFromFile(fin);
        fin.getline(buffer, 100);
        fin.getline(buffer, 100);
        text = Helper::GetStringFromBuffer(buffer);
    }
    virtual void PrintPost(bool datecheck = true) {//changes made

        Date d1 = Shared_date;
        Object* ptr = Shared_By;
        char* textptr = text;

        cout << "---";
        cout << ptr->GetFullName() << " ";
        if (content) {
            content->Print();
        }
        cout << "(";
        d1.Print();
        cout << ")\n";
        cout << textptr << endl;
        for (int i = 0; comments[i] != 0; i++)
        {
            comments[i]->Print();
        }
    }
    void ViewLikedList()
    {
        cout << "Post liked by:" << endl;
        for (int i = 0; Likedby[i] != 0; i++)//Trying that max 10 objects can like the post
        {
            Likedby[i]->PrintListView();

        }
    }

    char* GetPostID() {
        return post_id;
    }
    void AddComment(Comment* ptr) {
        for (int i = 0; i < 13; i++) {
            if (comments[i] == 0) {
                comments[i] = ptr;
                break;
            }
        }
    }
};
class Memory : public Post
{
private:
    Post* original_post;
public:
    Memory(Post* post, const char* id, const char* text, Object* postedby) : Post(id, text, postedby)
    {
        original_post = post;
    }

    ~Memory()     // destructor
    {
    }

    void PrintPost(bool datecheck = true)
    {
        Date d1 = Post::GetSharedDate();
        Object* ptr = Post::GetSharedby();
        char* textptr = Post::GetText();
        cout << "~~~";
        cout << ptr->GetFullName() << " ";
        cout << "shared a memory~~~" << endl;
        cout << textptr << endl;
        cout << "(";
        d1.Print();
        cout << ")\n";
        original_post->PrintPost();
    }
};
class Page : public Object
{
private:
    char* ID;
    char* Title;
public:
    Page() {
        ID = nullptr;
        Title = nullptr;
    }
    void ReadDataFromFilePages(ifstream& fin)
    {
        char buffer[50];
        fin >> buffer;
        ID = Helper::GetStringFromBuffer(buffer);
        fin.getline(buffer, 50);
        Title = Helper::GetStringFromBuffer(buffer);

    }
    ~Page() {
        delete[]ID;
        delete[]Title;
    }
    char* getpageid() {
        return ID;
    }
    char* getpagetitle() {
        return Title;
    }
    char* GetFullName()
    {
        return Title;
    }
    void Print()
    {
        cout << GetID() << '\t' << Title << endl;
    }

    void PrintListView()
    {
        // PrintID();
        cout << ID;
        cout << Title << endl;
    }
    void ViewTimeline()
    {
        cout << Title << " -- TIMELINE\n";
        for (int i = 0; Timeline[i] != 0; i++)
        {
            Timeline[i]->PrintPost();
        }
    }
    void ViewPage() {
        ViewTimeline();
    }
    void ViewHome()
    {
        for (int i = 0; Timeline[i] != 0; i++)
        {
            Timeline[i]->ViewRecent();
            cout << endl;
        }
    }
};
class User :public Object
{
private:
    char* id;
    char* Fname;
    char* Lname;
    User** FriendList;//null or 10 pointers max
    Page** LikedPages;//null or 10 pointers max
    int no_of_friends;
    int no_of_pages;
public:
    User() {
        no_of_friends = 0;
        no_of_pages = 0;
        id = nullptr;
        Fname = nullptr;
        Lname = nullptr;
        FriendList = new User * [10]();
        LikedPages = new Page * [10]();
    }
    void ReadDataFromFileUsers(ifstream& fin) {
        char temp[50];
        fin >> temp;
        id = Helper::GetStringFromBuffer(temp);
        fin >> temp;
        Fname = Helper::GetStringFromBuffer(temp);
        fin >> temp;
        Lname = Helper::GetStringFromBuffer(temp);
    }
    void AddFriend(User*& newfriend) {
        if (no_of_friends < 10) {
            FriendList[no_of_friends] = newfriend;
            no_of_friends++;
        }
    }
    void LikePage(Page*& newPage) {
        if (no_of_pages < 10)
        {
            LikedPages[no_of_pages] = newPage;
            no_of_pages++;
        }
    }
    void ViewTimeline()
    {
        cout << Fname << " " << Lname << " -- TIMELINE\n";
        for (int i = 0; Timeline[i] != 0; i++)
        {
            Timeline[i]->PrintPost();
        }
    }
    char* GetFullName()
    {
        char* fullname = Helper::StringConcatenate(Fname, Lname);
        return fullname;
    }
    void PrintListView()
    {
        //PrintID();
        cout << id;
        cout << " " << Fname << " " << Lname << endl;
    }
    void ViewFriendList()
    {
        cout << "-------------------------------------------------------------------------------------------------------------" << endl;
        cout << Fname << " " << Lname << " Friend List" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------" << endl;

        if (FriendList == nullptr) {
            cout << "No friends added yet." << endl;
        }
        else {
            bool hasFriends = false;
            for (int i = 0; i < 10; i++) {
                if (FriendList[i] != nullptr) {
                    hasFriends = true;
                    cout << FriendList[i]->id << " " << FriendList[i]->Fname << " " << FriendList[i]->Lname << endl;
                }
            }
            if (!hasFriends) {
                cout << "No friends added yet." << endl;
            }
        }
        cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    }
    void ViewLikedPages() {
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
        cout << Fname << " " << Lname << " Liked Pages" << endl;
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;

        if (LikedPages == nullptr) {
            cout << "No pages liked yet." << endl;
        }
        else {
            bool hasLikedPages = false;
            for (int i = 0; i < 10; i++) {
                if (LikedPages[i] != nullptr) {
                    hasLikedPages = true;
                    cout << LikedPages[i]->getpageid() << " " << LikedPages[i]->getpagetitle() << endl;
                }
            }
            if (!hasLikedPages) {
                cout << "No pages liked yet." << endl;
            }
        }
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    }
    void SeeMemory()
    {
        cout << Fname << " " << Lname << " --MEMORY\n";
        for (int i = 0; Timeline[i] != 0; i++)
        {
            Timeline[i]->ViewOldestPost();
        }
    }
    void ViewHome()
    {
        cout << Fname << " " << Lname << " - HomePage : " << endl;
        for (int i = 0; FriendList[i] != 0; i++)
        {
            int j = 0;
            for (j = 0; FriendList[i]->Timeline[j] != 0; j++)
            {
                FriendList[i]->Timeline[j]->ViewRecent();
            }
        }

        for (int i = 0; LikedPages[i] != 0; i++)
        {
            LikedPages[i]->ViewHome();
        }
    }
    static bool CheckTimeline(User* u1) {
        if (u1->Timeline[1] == 0)
        {
            return true;
        }
        else
            return false;
    }
    ~User()
    {//destructor
        delete[] id;
        delete[] Fname;
        delete[] Lname;
        delete[] FriendList;
        delete[] LikedPages;
    }
    char* getuserid() {
        return id;
    }
};
class Controller {
private:
    User** AllUsers;
    Page** AllPages;
    Post** posts;
    static int no_of_users;
    static int no_of_pages;
    //static int total_posts;
public:
    /*Controller() {
        AllUsers = new User*[no_of_users]();
        AllPages = new Page * [no_of_pages]();
        posts = new Post * [total_posts]();
    }*/
    void LoadAllUser(const char* filename) {
        ifstream fin(filename);
        fin >> no_of_users;
        AllUsers = new User * [no_of_users];
        for (int i = 0; i < no_of_users; i++) {
            AllUsers[i] = new User();
            AllUsers[i]->ReadDataFromFileUsers(fin);
        }
        fin.close();
    }
    void LoadAllPages(const char* filename) {
        ifstream fin(filename);
        fin >> no_of_pages;
        AllPages = new Page * [no_of_pages];
        for (int j = 0; j < no_of_pages; j++) {
            AllPages[j] = new Page();
            AllPages[j]->ReadDataFromFilePages(fin);
        }
        fin.close();
    }
    void LoadPostsFromFile(const char* filename)
    {
        ifstream fin(filename);
        int total_posts;
        fin >> total_posts;
        posts = new Post * [total_posts];   // total 10 posts memory allocated accordingly
        for (int i = 0; i < total_posts; i++)
        {
            posts[i] = new Post;
            posts[i]->ReadDatafromFilePosts(fin);
            char temp[10]; // for user id or page id
            fin >> temp;
            Object* sharedby = SearchObjectByID(temp);
            posts[i]->SetSharedBy(sharedby);
            sharedby->AddPostToTimeline(posts[i]);

            while (1)
            {
                fin >> temp;
                if (Helper::CompareString(temp, "-1") == 0)
                {
                    break;
                }
                Object* ptr = SearchObjectByID(temp);
                posts[i]->SetLikedBy(ptr);
            }
        }
        fin.close();    // closing posts file
    }
    void LoadAllComments(const char* filename) {
        ifstream fin(filename);
        int total_comments;
        fin >> total_comments;
        char* cid;
        char* postid;
        char* objid;
        char* commenttexts;
        for (int i = 0; i < total_comments; i++) {
            Comment* ptr = new Comment;
            char buffer[100];
            fin >> buffer;
            cid = Helper::GetStringFromBuffer(buffer);
            fin >> buffer;
            postid = Helper::GetStringFromBuffer(buffer);
            Post* check1 = SearchPostByID(postid);
            //check1->AddComment(ptr);
            fin >> buffer;
            objid = Helper::GetStringFromBuffer(buffer);
            Object* check2 = SearchObjectByID(objid);
            fin.getline(buffer, 80);
            commenttexts = Helper::GetStringFromBuffer(buffer);
            ptr->SetValues(cid, check2, commenttexts, postid);
            check1->AddComment(ptr);
            delete[] cid; cid = 0;
            delete[] postid; postid = 0;
            delete[] objid; objid = 0;
            delete[] commenttexts; commenttexts = 0;
        }
        fin.close();
    }
    void LoadAllActivities(const char* filename) {
        ifstream fin(filename);
        int total_activties;
        fin >> total_activties;
        char* buffer1 = new char[100];
        char* buffer2 = new char[100];
        int type = 0;
        Post* present;
        for (int i = 0; i < total_activties; i++) {
            Activity* ptr = new Activity;
            fin >> buffer1;
            fin >> type;
            fin.ignore();
            fin.getline(buffer2, 100);
            present = SearchPostByID(buffer1);
            ptr->SetActivity(type, buffer2);
            present->AddContent(ptr);//Kis post par content dalna so search sy return ho gi usmy dalna
        }
        fin.close();
        delete[]buffer1; buffer1 = 0;
        delete[]buffer2; buffer2 = 0;
    }
    User* SearchUserByID(const char* userid)
    {
        int size = no_of_users;
        for (int i = 0; i < size; i++) {
            if (Helper::CompareString(AllUsers[i]->getuserid(), userid) == 0) {
                return AllUsers[i];
            }

        }
        return nullptr;
    }
    Page* SearchPageByID(const char* pageid) {
        int size_of_pages = no_of_pages;
        for (int j = 0; j < size_of_pages; j++) {
            if (Helper::CompareString(AllPages[j]->getpageid(), pageid) == 0)//Changes made to my old code
            {
                return AllPages[j];
            }
        }
        return nullptr;
    }
    Object* SearchObjectByID(const char* id) {
        //for pages
        for (int i = 0; i < no_of_pages; i++)
        {
            if (Helper::CompareString(AllPages[i]->getpageid(), id) == 0) {
                return AllPages[i];
            }
        }
        //for users
        for (int i = 0; i < no_of_users; i++)
        {
            if (Helper::CompareString(AllUsers[i]->getuserid(), id) == 0) {
                return AllUsers[i];
            }
        }
    }
    Post* SearchPostByID(const char* id)
    {
        for (int i = 0; i < 12; i++) // loop for 11 as there r total 12 posts
        {
            if (Helper::CompareString(posts[i]->GetPostID(), id) == 0)
            {
                return posts[i];
            }
        }
        return nullptr;
    }

    void LinkUsersAndPages()
    {
        ifstream fin("userspages.txt");
        char buffer[50];
        fin >> buffer;
        int size = no_of_users;
        for (int k = 0; k < (size - 1); k++) {
            User* temp = SearchUserByID(buffer);
            fin >> buffer;
            while (buffer[0] != '-' || buffer[1] != '1')
            {
                User* present = SearchUserByID(buffer);
                if (present != nullptr) {
                    temp->AddFriend(present);
                }
                fin >> buffer;
            }
            fin >> buffer;
            while (buffer[0] != '-' || buffer[1] != '1')
            {
                Page* pages = SearchPageByID(buffer);
                if (pages != nullptr) {
                    temp->LikePage(pages);
                }
                fin >> buffer;

            }
            fin >> buffer;
        }
        fin.close();
    }
    void ShareMemory(const char* id, const char* text, Object* person)
    {
        Post* ptr = SearchPostByID(id);
        Memory* memoryptr = new Memory(ptr, id, text, person);
        person->AddPostToTimeline(memoryptr);
    }
    ~Controller()
    {
        for (int i = 0; i < no_of_users; i++) {
            delete AllUsers[i];
        }
        delete[] AllUsers;
        for (int j = 0; j < no_of_pages; j++) {
            delete AllPages[j];
        }
        delete[] AllPages;
        /*  for (int k = 0; k < 12; k++) {
               delete posts[k];
           }
           delete[] posts;*/
    }
    void LoadData()
    {
        LoadAllUser("users.txt"); //Keep it easily configurable
        LoadAllPages("pages.txt"); //Keep it easily configurable
        LinkUsersAndPages();
        //run("u7");
        LoadPostsFromFile("posts.txt");
        LoadAllComments("comments.txt");
        LoadAllActivities("activities.txt");
        run("u7");
    }
    void run(const char* specificuser) {
        User* user = SearchUserByID(specificuser);
        user->ViewFriendList();
        user->ViewLikedPages();
        cout << "\n\n\n-------------------------------------PHASE 2 STARTS -------------------------------------------\n";
        Date::SetCurrDate(17, 4, 24);
        cout << "\n\nCommand : View timeline" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        user->ViewTimeline();
        cout << "--------------------------------------------------------------------------------\n";
        Post* post1;
        char p1[] = "post5";
        post1 = SearchPostByID(p1);
        cout << "\n\nCommand : View liked list (post5)" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        post1->ViewLikedList();
        cout << "--------------------------------------------------------------------------------\n";
        cout << "\n\nCommand : Likepost(post5)\nCommand : View liked list" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        post1->SetLikedBy(user);
        post1->ViewLikedList();
        cout << "--------------------------------------------------------------------------------\n";
        Page* p;
        char arr[] = "p1";
        p = SearchPageByID(arr);
        cout << "\n\nCommand : View page (p1)" << endl;
        p->ViewPage();
        cout << "------------------------------------------------------------------------------------\n";
        cout << "\n\n\n-------------------------------------PHASE 3 STARTS -------------------------------------------\n";
        Date::SetCurrDate(17, 4, 2024);
        cout << "\n\nCommand : View home" << endl;
        user->ViewHome();
        user->ViewTimeline();
        cout << "----------------------------------------------------------------------------------------------------------";
        Post* post2;
        Post* post3;
        char p2[] = "post8";
        char p3[] = "post4";
        post2 = SearchPostByID(p2);
        post3 = SearchPostByID(p3);
        char c1[] = " Thanks for the wishes";
        char c2[] = " Good Luck for your result";

        cout << "\n\nCommand : PostComment (post4, Good Luck for your result)" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        post3->PostComment(post3, user, c2);
        post3->PrintPost();
        cout << "--------------------------------------------------------------------------------\n";

        cout << "\n\nCommand : PostComment (post 8, thanks for the wishes)" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        post2->PostComment(post2, user, c1);
        post2->PrintPost();
        cout << "--------------------------------------------------------------------------------\n";

        cout << "\n\nCommand : See your memories" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        user->SeeMemory();
        cout << "--------------------------------------------------------------------------------\n";


        cout << "\n\nCommand : ShareMemory(post10, Never thought I will be specialist in this field)" << endl;
        cout << "--------------------------------------------------------------------------------\n";
        /* if (User::CheckTimeline(user) == 0)
         {*/
        ShareMemory("post10", "Never thought I will be specialist in this field...", user);
        user->ViewTimeline();
        //}
        cout << "--------------------------------------------------------------------------------\n";
    }
};
int Controller::no_of_pages = 0;
int Controller::no_of_users = 0;
//int Controller::total_posts = 0;
int main() {
    Controller mainApp;
    mainApp.LoadData();
    return 0;
}

