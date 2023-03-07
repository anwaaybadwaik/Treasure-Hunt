#include <iostream>
#include <string>
#include <vector>
using namespace std;

// In this challenge, the objective is to implement a Database class which is templated on the table schema. A Database class will store a collection of records, where each record will consist of a key and a value, which themselves are collection of fields (also called the schema). For example, in a student database, the key could be the student roll number (of type string), while the value could consist of fields like name, DOB, stream, semester, etc. The key may also consist of multiple fields, for example, in a database storing details about BTP/DDP guides of students, the key would be student roll number and faculty name. The point is that for every key instance, there would be at most one record with that key in the database.

// The Database class will be templated on classes Key and Value. You need to create a Record class which stores all details of a record (i.e. the Key and the Value). The Database class should then store all the records using the DoublyLinkedList class created in challenge-1. You should then implement the following methods in the Database class:

// isPresent(Key & k) returns true if the input key is present in the database, otherwise false. selectRecord(Key & k) returns the record containing the key (you can assume that k will be present).

// selectRangeRecord(Key & rangeStart, Key & rangeEnd) returns a vector containing all the records in the database whose key lies between rangeStart and rangeEnd (inclusive).

// updateRecord(Key & k, Value & v) updates the record in the database whose key is k with value v. If k is not present, there is no change in the database.

// deleteRecord(Key & k) deletes the record in the database whose key is k. If k is not present, there is no change in the database.

// insertRecord(Key & k, Value & v) inserts a new record in the database with key k and value v. If k is already present, there is no change in the database.

// getMinRecord() and getMaxRecord() return the minimum and maximum record respectively (you can assume that the database won't be empty).

// getallRecords() returns a vector containing all the records in the database.

// To implement these operations efficiently, you should ensure that while adding/deleting records from the linked list, it remains sorted in increasing order according to Key. Now, while searching for a record with a specific Key k, you should implement a binary search-like procedure which should make at most  calls to atIndex method of DoublyLinkedList, where  is the number of records in the database. To summarize, use the fact that the linked list is sorted to implement the methods as efficiently as possible. Note that you should not change the DoublyLinkedList implementation from challenge-1. Your implementation of Database class should call appropriate methods of the DoublyLinkedList class. You need not worry about the time complexity of the methods in the DoublyLinkedList implementation.

template <class Key, class Value>
class Database {
public:
    class Record {
    private:
        Key k;
        Value v;

    public:
        Record(const Key &ik = Key(),const Value &iv = Value()) : k(ik), v(iv) {}
        Key &getKey() { return k; }
        Value &getValue() { return v; }
        void setValue(Value &iv) { v = iv; }
    };

private:
        /*use the DoublyLinkedList class created in challenge 1*/
    template <class Object>
    class DoublyLinkedList
    {
    private:
        struct Node
        {
            Object data;
            Node *next;
            Node *prev;
            // Constructor for the Node
            Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
                : data(d), prev(p), next(n) {}
            Node(Node *p) : data(p->data), prev(p->prev), next(p->next) {}
        };

        Node *head; // sentinel node at the beginning
        Node *rear; // sentinel node at the end

    public:
        /*TODO: Define a constructor for DoublyLinkedList here, allocating the sentinel nodes*/
        DoublyLinkedList()
        {
            head = new Node;
            rear = new Node;
            head->next = rear;
            rear->prev = head;
        }

        class Iterator
        {
        private:
            Node *current;

        public:
            Iterator(Node *inp) : current(inp) {}
            Object &operator*() { return current->data; }

            Iterator &operator=(Iterator &rhs)
            {
                this->current = rhs.current;
                return *this;
            }

            Iterator &operator++()
            {
                this->current = this->current->next;
                return *this;
            }

            Iterator operator--()
            {
                this->current = this->current->prev;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator old = *this;
                this->current = this->current->next;
                return old;
            }

            bool operator==(Iterator rhs)
            {
                return this->current == rhs.current;
            }

            bool operator!=(Iterator rhs)
            {
                return !(*this == rhs);
            }

            /*TODO: You can add more methods here */

            friend class DoublyLinkedList<Object>;
        };

        Iterator begin() { return Iterator(head->next); }

        Iterator end() { return Iterator(rear); }

        Iterator insert(Iterator itr, Object &o)
        {
            Node *p = new Node(o, itr.current->prev, itr.current);
            itr.current->prev->next = p;
            itr.current->prev = p;
            itr.current = p;

            return itr;
        }
        Iterator erase(Iterator itr)
        {
            Node *To_delete;
            To_delete = itr.current;
            itr.current->prev->next = itr.current->next;
            itr.current->next->prev = itr.current->prev;
            itr.current = itr.current->next;
            return itr;
        }
        Iterator atIndex(int p)
        {
            Node *x;
            int count = 0;
            for (x = head->next; x != rear; x = x->next)
            {
                if (count == p)
                {
                    break;
                }
                else
                {
                    count++;
                }
            }

            return Iterator(x);
        }
        int indexOf(Iterator itr)
        {
            int count = 0;
            Node *p;
            for (p = head->next; p != rear; p = p->next)
            {
                if (p == itr.current)
                {
                    break;
                }
                else
                {
                    count++;
                }
            }
            return count;
        }
        
        int size()
        {
            int count = 0;
            Node *p;
            for (p = head->next; p != rear; p = p->next)
            {
                count++;
            }
            return count;
        }

        void display()
        {
            for (auto it = begin(); it != end(); it++)
                cout << *it << " ";
            cout << endl;
        }

        DoublyLinkedList(const DoublyLinkedList &rhs)
        {
            DoublyLinkedList();
            for (auto it = rhs.begin(); it != rhs.end(); it++)
            {
                insert(end(), *it);
            }
        }
    };
    DoublyLinkedList<Record> list;

public:
    void insertRecord(Key &k, Value &v) {
        Record R(k, v);
        auto it = list.begin();
        //89 79 85
        int l = 0; int r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        auto it1 = list.atIndex(l);
        list.insert(it1, R);
    }

    bool isPresent(Key &k) {
        //binary search
        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k) {
                return true;
            } else if ((*it).getKey() < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return false;
    }

    vector<Record> selectRangeRecord(Key &k1, Key &k2) {
        vector<Record> v;
        //binary search
        auto it1 = list.begin();
        auto it2 = list.begin();

        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k1) {
                it1 = it;
                break;
            } else if ((*it).getKey() < k1) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k2) {
                it2 = it;
                break;
            } else if ((*it).getKey() < k2) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        it2++;
        for(auto it = it1; it != it2; it++)
            v.push_back(*it);
        return v;
    }

    void deleteRecord(Key &k) {
        //binary search
        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k) {
                list.erase(it);
                return;
            } else if ((*it).getKey() < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }

    Record selectRecord(Key &k) {
        //binary search
        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k) {
                return *it;
            } else if ((*it).getKey() < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return Record();
    }

    void updateRecord(Key &k, Value &v){
        //binary search
        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k) {
                (*it).setValue(v);
                return;
            } else if ((*it).getKey() < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }

    void updateRangeRecord(Key &k1,Key &k2, Value &v){
        auto it1 = list.begin();
        auto it2 = list.begin();

        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k1) {
                it1 = it;
                break;
            } else if ((*it).getKey() < k1) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k2) {
                it2 = it;
                break;
            } else if ((*it).getKey() < k2) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        it2++;
        for(auto it = it1; it != it2; it++) {
            (*it).setValue(v);
        }
    }

    void deleteRangeRecord(Key &k1, Key &k2) {
        // binary search
        auto it1 = list.begin();
        auto it2 = list.begin();
        int l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k1) {
                it1 = it;
                break;
            } else if ((*it).getKey() < k1) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        l = 0, r = list.size() - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto it = list.atIndex(mid);
            if ((*it).getKey() == k2) {
            //71 79 84
                it2 = it;
                break;
            } else if ((*it).getKey() < k2) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        it2++;
        for(auto it = it1; it != it2; it++) {
            list.erase(it);
        }
    }

    Record getMinRecord() {
        auto min = list.begin();
        return *min;
    }

    Record getMaxRecord() {
        auto max = list.end();
        --max;
        return *max;
        
    }

    vector<Record> getallRecords() {
        vector<Record> v;
        for(auto it = list.begin(); it != list.end(); it++) {
            v.push_back(*it);
        }
        return v;
    }

};

class StudentsKey {
public:
    string rollNo;
    StudentsKey(string inp = "") : rollNo(inp) {}
    bool operator<(StudentsKey &rhs) { return rollNo < rhs.rollNo; }
    bool operator==(StudentsKey &rhs) { return rollNo == rhs.rollNo; }
    bool operator >=(StudentsKey &rhs) { return rollNo >= rhs.rollNo; }
    bool operator <=(StudentsKey &rhs) { return rollNo <= rhs.rollNo; }
    bool operator >(StudentsKey &rhs) { return rollNo > rhs.rollNo; }
    friend ostream & operator<<(ostream & out, StudentsKey &k);
};

ostream & operator<<(ostream & out, StudentsKey &k) { 
    out << k.rollNo;
  	return out;
}

class StudentsValue {
public:
    string name;
    string hostel;
    float cgpa;
    StudentsValue(string n ="", string h ="", float c = 10.0) : name(n), hostel(h), cgpa(c) {}

    friend ostream & operator<<(ostream & out, StudentsValue &v);
};

ostream & operator<<(std::ostream & out, StudentsValue &v) {
    out << v.name << " " << v.hostel << " " << v.cgpa;
    return out;
}

class FacultyKey {
public:
    string empId;
    FacultyKey(string inp = "") : empId(inp) {}
    bool operator<(FacultyKey &rhs) { return empId < rhs.empId; }
    bool operator==(FacultyKey &rhs) { return empId == rhs.empId; }
    bool operator >=(FacultyKey &rhs) { return empId >= rhs.empId; }
    bool operator <=(FacultyKey &rhs) { return empId <= rhs.empId; }
    bool operator >(FacultyKey &rhs) { return empId > rhs.empId; }
    friend ostream & operator<<(ostream & out, FacultyKey &k);
};

ostream & operator<<(ostream & out, FacultyKey &k) { 
    out << k.empId;
 	return out;
}

class FacultyValue {
public:
    string name;
    string designation;
    float salary;
    FacultyValue(string n = "", string d = "", float s = 10.0) : name(n), designation(d), salary(s) {}
    friend ostream & operator<<(ostream & out, FacultyValue &v);
};

ostream & operator<<(std::ostream & out, FacultyValue &v) {
    out << v.name << " " << v.designation << " " << v.salary;
    return out;
}

class CourseKey {
public:
    string courseId;
    CourseKey(string inp = "") : courseId(inp) {}
    bool operator<(CourseKey &rhs) { return courseId < rhs.courseId; }
    bool operator==(CourseKey &rhs) { return courseId == rhs.courseId; }
    bool operator >=(CourseKey &rhs) { return courseId >= rhs.courseId; }
    bool operator <=(CourseKey &rhs) { return courseId <= rhs.courseId; }
    bool operator >(CourseKey &rhs) { return courseId > rhs.courseId; }
    friend ostream & operator<<(ostream & out, CourseKey &k);
};

ostream & operator<<(ostream & out, CourseKey &k) { 
    out << k.courseId;
    return out;
}

class CourseValue {
public:
    string name;
    string semester;
    string facultyName;
    CourseValue(string n = "", string s = "", string f = "") : name(n), semester(s), facultyName(f) {}
    friend ostream & operator<<(ostream & out, FacultyValue &v);
};

ostream & operator<<(std::ostream & out, CourseValue &v) {
    out << v.name << " " << v.semester << " " << v.facultyName;
    return out;
}

int main() {
    int command;
    bool b;
    int BREAKING_COMMAND = 50;

    Database<StudentsKey, StudentsValue> student_db;
    Database<FacultyKey, FacultyValue> faculty_db;
    Database<CourseKey, CourseValue> course_db;

    while (true) {
        cin >> command;
        if (command == BREAKING_COMMAND) {
            break;
        }

        if (command == 1) { /*insert record*/
            int numberOfRecords = 0; /*number of records to be inserted*/
            cin >> numberOfRecords;

            while (numberOfRecords--) {

                string database;
                cin >> database;

                if (database == "STUDENT") {
                    string rollNo, name, hostel;
                    float cgpa;
                    cin >> rollNo >> name >> hostel >> cgpa;

                    StudentsKey k(rollNo);
                    StudentsValue v(name, hostel, cgpa);
                    student_db.insertRecord(k, v);
                } else if (database == "FACULTY") {
                    string empId, name, designation;
                    float salary;
                    cin >> empId >> name >> designation >> salary;

                    FacultyKey k(empId);
                    FacultyValue v(name, designation, salary);
                    faculty_db.insertRecord(k, v);
                } else {
                    string courseId, name, semester, facultyName;
                    cin >> courseId >> name >> semester >> facultyName;

                    CourseKey k(courseId);
                    CourseValue v(name, semester, facultyName);
                    course_db.insertRecord(k, v);
                }
            }

        } else if (command == 2) { /*check whether the key is present*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rollNo;
                cin >> rollNo;

                StudentsKey k(rollNo);
                b = student_db.isPresent(k);
                cout << b << endl;
            } else if (database == "FACULTY") {
                string empId;
                cin >> empId;

                FacultyKey k(empId);
                b = faculty_db.isPresent(k);
                cout << b << endl;
            } else {
                string courseId;
                cin >> courseId;

                CourseKey k(courseId);
                b = course_db.isPresent(k);
                cout << b << endl;
            }

        } else if (command == 3) {
            string database; /*returns the record containing the key*/
            cin >> database;

            if (database == "STUDENT") {
                string rollNo;
                cin >> rollNo;

                StudentsKey k(rollNo);
                auto r = student_db.selectRecord(k);
            //78 79 84 72 73 78 71
                cout << r.getKey() << " " << r.getValue() << endl;
            } else if (database == "FACULTY") {
                string empId;
                cin >> empId;

                FacultyKey k(empId);
                auto r = faculty_db.selectRecord(k);
                cout << r.getKey() << " " << r.getValue() << endl;
            } else {
                string courseId;
                cin >> courseId;

                CourseKey k(courseId);
                auto r = course_db.selectRecord(k);
                cout << r.getKey() << " " << r.getValue() << endl;
            }

        } else if (command == 4) { /*returns a vector containing all the records in the database
                                     whose key lies between rangeStart and rangeEnd (inclusive).*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                StudentsKey rs(rangeStart);
                StudentsKey re(rangeEnd);
                auto lst = student_db.selectRangeRecord(rs, re);
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else if (database == "FACULTY") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                FacultyKey rs(rangeStart);
                FacultyKey re(rangeEnd);
                auto lst = faculty_db.selectRangeRecord(rs, re);
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                CourseKey rs(rangeStart);
                CourseKey re(rangeEnd);
                auto lst = course_db.selectRangeRecord(rs, re);
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            }

        } else if (command == 5) { /*updates the record in the database whose key is k with value v.
                                     If k is not present, there is no change in the database.*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rollNo, name, hostel;
                float cgpa;
                cin >> rollNo >> name >> hostel >> cgpa;

                StudentsKey k(rollNo);
                StudentsValue v(name, hostel, cgpa);
                student_db.updateRecord(k, v);
            } else if (database == "FACULTY") {
                string empId, name, designation;
                float salary;
                cin >> empId >> name >> designation >> salary;

                FacultyKey k(empId);
                FacultyValue v(name, designation, salary);
                faculty_db.updateRecord(k, v);
            } else {
                string courseId, name, semester, facultyName;
                cin >> courseId >> name >> semester >> facultyName;

                CourseKey k(courseId);
                CourseValue v(name, semester, facultyName);
                course_db.updateRecord(k, v);
            }

        } else if (command == 6) { /*updates all records in the database whose key lies between
                                     rangeStart and rangeEnd, with value v (inclusive).*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rangeStart, rangeEnd, name, hostel;
                float cgpa;
                // 87 69
                cin >> rangeStart >> rangeEnd >> name >> hostel >> cgpa;

                StudentsKey rs(rangeStart);
                StudentsKey re(rangeEnd);
                StudentsValue v(name, hostel, cgpa);
                student_db.updateRangeRecord(rs, re, v);
            } else if (database == "FACULTY") {
                string rangeStart, rangeEnd, name, designation;
                float salary;
                cin >> rangeStart >> rangeEnd >> name >> designation >> salary;

                FacultyKey rs(rangeStart);
                FacultyKey re(rangeEnd);
                FacultyValue v(name, designation, salary);
                faculty_db.updateRangeRecord(rs, re, v);
            } else {
                string rangeStart, rangeEnd, name, semester, facultyName;
                cin >> rangeStart >> rangeEnd >> name >> semester >> facultyName;

                CourseKey rs(rangeStart);
                CourseKey re(rangeEnd);
                CourseValue v(name, semester, facultyName);
                course_db.updateRangeRecord(rs, re, v);
            }

        } else if (command == 7) { /*deletes the record with key k.*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rollNo;
                cin >> rollNo;

                StudentsKey k(rollNo);
                student_db.deleteRecord(k);
            } else if (database == "FACULTY") {
                string empId;
                cin >> empId;

                FacultyKey k(empId);
                faculty_db.deleteRecord(k);
            } else {
                string courseId;
                cin >> courseId;

                CourseKey k(courseId);
                course_db.deleteRecord(k);
            }

        } else if (command == 8) { /*deletes all records with key between rangeStart and rangeEnd (inclusive).*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                StudentsKey rs(rangeStart);
                StudentsKey re(rangeEnd);
                student_db.deleteRangeRecord(rs, re);
            } else if (database == "FACULTY") {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                FacultyKey rs(rangeStart);
                FacultyKey re(rangeEnd);
                faculty_db.deleteRangeRecord(rs, re);
            } else {
                string rangeStart, rangeEnd;
                cin >> rangeStart >> rangeEnd;

                CourseKey rs(rangeStart);
                CourseKey re(rangeEnd);
                course_db.deleteRangeRecord(rs, re);
            }

        } else if (command == 9) { /*return the minimum record*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                auto r = student_db.getMinRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else if (database == "FACULTY") {
                auto r = faculty_db.getMinRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else {
                auto r = course_db.getMinRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            }

            // 71 79 84 
        } else if (command == 10) { /*return the maximum record*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                auto r = student_db.getMaxRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else if (database == "FACULTY") {
                auto r = faculty_db.getMaxRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            } else {
                auto r = course_db.getMaxRecord();
                cout << r.getKey() << " " << r.getValue() << endl;
            }

        } else if (command == 11) { /*returns a vector containing all the records in the database.*/
            string database;
            cin >> database;

            if (database == "STUDENT") {
                auto lst = student_db.getallRecords();
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else if (database == "FACULTY") {
                auto lst = faculty_db.getallRecords();
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            } else {
                auto lst = course_db.getallRecords();
                for (auto r : lst) {
                    cout << r.getKey() << " " << r.getValue() << endl;
                }
            }

        } else {
            cout << "INVALID COMMAND!" << endl;
            break;
            //???????
        }
    }
}
