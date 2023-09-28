#include <iostream>
#include <vector>
using namespace std;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

class SET {
public:
    vector<int> s;

    SET(vector<int> x) {
        s = x;
    }

    void Insert(int q) { 
        int n = s.size();
        for( int j=0;j<s.size();j++){
            if(q==s[j]){
                cout<<s.size()<<endl;
                return;
            }
        }
        s.push_back(q);
        quickSort (s, 0 , n-1);
        cout << s.size() << endl;
    }

    void Delete(int q) {
        int n = s.size();
        for (int a = 0; a < n; a++) {
            if (s[a] == q) {
                s.erase(s.begin() + a);
                break;
            }
        }
        cout << s.size() << endl;
    }

    void Belongs_To(int q) {
        for (int num : s) {
            if (num == q) {
                cout << 1 << endl;
            }
        }
        cout << 0 << endl;
    }

    void Size() {
        cout << s.size() << endl;
    }

    vector<int> Union(){
        return s;
    }

    vector<int> Intersection(){
        return s;
    }

    vector<int> Difference(){
        return s;
    }

    vector<int> Symmetric_Difference(){
        return s;
    }

    void Print() {
        int n = s.size();
	quickSort (s, 0 , n-1);

	if ( n ==0) {
	cout << endl;}
	else {
        for (int a = 0; a < n-1; a++) {
            cout << s[a] << ",";
        }
        cout << s[n - 1] << endl;}
    }
};

int main() {
    vector<SET> PointersToSet;
    SET newset({});
 	int c;
	while (cin >> c){
       
        // used to find the commands we need to execute.

        if (c == 1) {
            int a;
            cin >> a; // a is used to access the set from PointersToSet 
            if (a >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
            int b;
            cin >> b; // the element we want to insert
            PointersToSet[a].Insert(b);
        }

        else if (c == 2) {
            int a; // to access the set.
            cin >> a;
            int b;
            cin >> b; // the element we want to delete
            if (a >= PointersToSet.size()) {
                cout << -1 << endl;
            } else {
                
                PointersToSet[a].Delete(b);
            }
        }

        else if (c == 3) {
            int a; // to access the set.
            cin >> a;
            int b;
            cin >> b; // the element we want to check membership
            if (a >= PointersToSet.size()) {
                cout << -1 << endl;
            } else {
                
                PointersToSet[a].Belongs_To(b);
            }
        }

        else if (c == 4){
            int a, b;
            cin >> a;
            cin >> b;
            if (a >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
            else if (b >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
	else if (a >=PointersToSet.size() && b >=PointersToSet.size()){
		newset = SET({});
                PointersToSet.push_back(newset);
		newset = SET({});
                PointersToSet.push_back(newset);
		}
            vector<int> x;
            vector <int> y;
            x = PointersToSet[a].Union();
            y = PointersToSet[b].Union();
            auto isElementPresent = [](int element, const vector<int>& vec) -> bool {
            for (const int& num : vec) {
                if (num == element) {
                    return true;
                }
            }
            return false;
            };

            // Insert elements from y into x if they are not already present
            for (const int& element : y) {
                if (!isElementPresent(element, x)) {
                    x.push_back(element);
                }
            }
            quickSort(x, 0, x.size()-1);
            PointersToSet[a] = SET (x);
            PointersToSet[a].Size();
        }

        else if (c == 5){
            int a, b;
            cin >> a;
            cin >> b;
            if (a >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
            else if (b >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
	else if (a >=PointersToSet.size() && b >=PointersToSet.size()){
		newset = SET({});
                PointersToSet.push_back(newset);
		newset = SET({});
                PointersToSet.push_back(newset);
		}
            vector<int> x;
            vector <int> y;
            x = PointersToSet[a].Intersection();
            y = PointersToSet[b].Intersection();
            
            auto isElementPresent = [](int element, const vector<int>& vec) -> bool {
            for (const int& num : vec) {
                if (num == element) {
                    return true;
                }
            }
            return false;
        };

            // Traverse the first vector and remove elements not present in the second vector
            auto it = x.begin();
            while (it != x.end()) {
                if (!isElementPresent(*it, y)) {
                    it = x.erase(it);
                } else {
                    ++it;
                }
        }
            quickSort(x, 0, x.size()-1);
            PointersToSet[a] = SET (x);
            PointersToSet[a].Size();
        }

        else if (c == 6) {
            int a; // to access the set.
            cin >> a;
            if (a >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
            PointersToSet[a].Size();
        }

        else if (c == 7){
            int a, b;
            cin >> a;
            cin >> b;
            if (a >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
            else if (b >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
	else if (a >=PointersToSet.size() && b >=PointersToSet.size()){
		newset = SET({});
                PointersToSet.push_back(newset);
		newset = SET({});
                PointersToSet.push_back(newset);
		}
            vector<int> x;
            vector <int> y;
            x = PointersToSet[a].Difference();
            y = PointersToSet[b].Difference();


            auto isElementPresent = [](int element, const std::vector<int>& vec) -> bool {
            for (const int& num : vec) {
                if (num == element) {
                    return true;
                }
            }
            return false;
        };

            // Traverse the first vector and remove elements present in the second vector
            auto it = x.begin();
            while (it != x.end()) {
                if (isElementPresent(*it, y)) {
                    it = x.erase(it);
                } else {
                    ++it;
                }
            }
            quickSort(x, 0, x.size()-1);
            PointersToSet[a] = SET (x);

            PointersToSet[a].Size();
        }

        else if (c == 8) {
            int a, b;
            cin >> a;
            cin >> b;
            if (a >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
            else if (b >=PointersToSet.size()) {
                newset = SET({});
                PointersToSet.push_back(newset);
                
            }
	else if (a >=PointersToSet.size() && b >=PointersToSet.size()){
		newset = SET({});
                PointersToSet.push_back(newset);
		newset = SET({});
                PointersToSet.push_back(newset);
		}
            vector<int> x;
            vector <int> y;
            x = PointersToSet[a].Symmetric_Difference();
            y = PointersToSet[b].Symmetric_Difference();

            auto isElementPresent = [](int element, const std::vector<int>& vec) -> bool {
            for (const int& num : vec) {
                if (num == element) {
                    return true;
                }
            }
            return false;
        };

            std::vector<int> tempVec1 = x;
            x.clear();

            // Insert unique elements from tempVec1 into vec1
            for (const int& element : tempVec1) {
                if (!isElementPresent(element, y)) {
                    x.push_back(element);
                }
            }

            // Insert unique elements from vec2 into vec1
            for (const int& element : y) {
                if (!isElementPresent(element, tempVec1)) {
                    x.push_back(element);
                }
            }
            quickSort(x, 0, x.size()-1);
            PointersToSet[a] = SET (x);
            PointersToSet[a].Size();

        }
    
        else if (c == 9) {
            int a; // to access the set.
            cin >> a;
            if (a >= PointersToSet.size()) {
                cout << endl;
            } else {
                PointersToSet[a].Print();
            }
        }
}
    


    return 0;
};
