/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;

int no_of_digits(int a){
    int b = abs(a);
    int t=0;
    while(b>0){
        t++;
        b=b/10;
    }
    return t;
}

UnlimitedInt:: UnlimitedInt(){     // this constructor will make 0 as the the object
    size =1;
    sign = 0;         
    capacity =1;
    unlimited_int = new int[1]();
}

UnlimitedInt:: UnlimitedInt(string s){
    int q = s.size();
    if(q==0){     // 0 case
        size =1;
        sign = 0;         
        capacity =1;
        unlimited_int = new int[1]();
    }
    else if(s[0]=='0'){   //0 case
        size =1;
        sign = 0;         
        capacity =1;
        unlimited_int = new int[1]();
    }
    else{
        if(s[0]=='-'){
            size = q-1;          // negative case
            capacity = q-1;
            sign = -1;
            unlimited_int = new int[q-1]();
            for(int i=1; i<q; i++){
                unlimited_int[i-1] = int(s[i])-48;
            }
        }
        else{
            size = q;
            capacity = q;       // positive case
            sign = 1;
            unlimited_int = new int[q-1]();
            for(int i=0; i<q; i++){
                unlimited_int[i] = int(s[i])-48;
            }
        }
    }
}

UnlimitedInt:: UnlimitedInt(int num){
    if(num==0){     // 0 case
        size =1;
        sign = 0;         
        capacity =1;
        unlimited_int = new int[1]();
    }
    else if(num<0){        // negative case
        int d = no_of_digits(num);
        size =d;
        sign = -1;         
        capacity =d;
        unlimited_int = new int[d]();
        for(int i=d-1; i>=0; i--){
            int r = abs(num)%10;
            unlimited_int[i]=r;
            num = num/10;
        }
    }
    else{             // positve case
        int d = no_of_digits(num);
        size =d;
        sign = 1;         
        capacity =d;
        unlimited_int = new int[d]();
        for(int i=d-1; i>=0; i--){
            int r = (num)%10;
            unlimited_int[i]=r;
            num = num/10;
        }
    }
}

UnlimitedInt:: UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    capacity = cap;
    sign = sgn;
    size = sz;
    unlimited_int = new int[size];
    for(int t=0; t<size; t++){
        unlimited_int[t] = ulimited_int[t];    // creating a copy always so that I don't change the argument ever
    }
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}

int UnlimitedInt::get_size()
{
    return size;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

int is_bigger_mod(UnlimitedInt* num1, UnlimitedInt* num2){
    int sz1 = num1->get_size();
    int sz2 = num2->get_size();    
    if(sz1 > sz2){
        return 1;
    }
    else if(sz1  < sz2){
        return -1;
    }
    else{
        int* arr1 = num1->get_array();
        int* arr2 = num2->get_array();
        for(int k=0; k<sz1; k++){
            if(arr2[k]>arr1[k]){
                return -1;
            }
            else if(arr2[k]<arr1[k]){
                return 1;
            }
        }
        return 0;
    }
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{   int sn1= i1->sign;
    int sn2 = i2->sign;
    int sz1 = i1->size;
    int sz2 = i2->size;                 
    int cap1 = i1->capacity;
    int cap2 = i2->capacity;
    if (sn1 == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(i2->get_array(), i2->get_capacity(), i2->get_sign(), i2->get_size());
        return temp;
    }
    else if (sn2 == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(i1->get_array(), i1->get_capacity(), i1->get_sign(), i1->get_size());
        return temp;
    }
    else if (sn1 * sn2 > 0)
    {
        int final_sn = i1->get_sign();
        int s1;
        int s2;
        int *arr1;
        int *arr2;
        if (sz1 > sz2)
        {
            s1 = i1->get_size();
            s2 = i2->get_size();
            arr1 = i1->get_array();
            arr2 = i2->get_array();
        }
        else
        {
            s1 = i2->get_size();
            s2 = i1->get_size();
            arr1 = i2->get_array();
            arr2 = i1->get_array();
        }
        int max1 = s1 + 1;
        int *res = new int[max1]();
        int carry = 0;

        for (int i = 0; i < s2; i++)
        {
            int x = arr1[s1 - i - 1] + arr2[s2 - i - 1] + carry;
            res[max1 - 1 - i] = x % 10;
            carry = x / 10;
        }
        for (int i = s2; i < s1; i++)
        {
            int x = arr1[s1 - i - 1] + carry;
            res[max1 - 1 - i] = x % 10;
            carry = x / 10;
        }

        if (carry != 0)
        {
            res[0] = carry;
            UnlimitedInt *temp = new UnlimitedInt(res, max1, final_sn, max1);
            delete[] res;
            return temp;
        }
        else
        {
            max1 = s1;
            int *final_res = new int[max1];
            for (int i = 0; i < max1; i++)
            {
                final_res[i] = res[i + 1];
            }
            delete[] res;
            UnlimitedInt *temp = new UnlimitedInt(final_res, max1, final_sn, max1);
            delete[] final_res;
            return temp;
        }
    }
    else
    {
        int more = is_bigger_mod(i1, i2);
        if (more == 0)
        {
            UnlimitedInt *temp = new UnlimitedInt();
            return temp;
        }
        else
        {
            int nsign;
            int *a, *b;
            int s1, s2;
            if (more == 1)
            {
                nsign = i1->get_sign();
                a = i1->get_array();
                s1 = i1->get_size();
                b = i2->get_array();
                s2 = i2->get_size();
            }
            else if (more == -1)
            {
                nsign = -1 * (i1->get_sign());
                a = i2->get_array();
                s1 = i2->get_size();
                b = i1->get_array();
                s2 = i1->get_size();
            }

            int final_sz = s1;
            int *res = new int[final_sz]{};
            int carry = 0;

            for (int i = 0; i < s2; i++)
            {
                int curr = a[s1 - i - 1] - b[s2 - i - 1] + carry;
                if (curr >= 0)
                {
                    res[final_sz - 1 - i] = curr;
                    carry = 0;
                }
                else
                {
                    res[final_sz - 1 - i] = curr + 10;
                    carry = -1;
                }
            }
            for (int i = s2; i < s1; i++)
            {
                int curr = a[s1 - i - 1] + carry;
                res[final_sz - 1 - i] = curr % 10;
                if (curr >= 0)
                {
                    res[final_sz - 1 - i] = curr;
                    carry = 0;
                }
                else
                {
                    res[final_sz - 1 - i] = curr + 10;
                    carry = -1;
                }
            }
            for (int i = 0; i < s1; i++)
            {
                if (res[i] == 0)
                {
                    final_sz--;
                }
                else
                {
                    break;
                }
            }
            int *final_res = new int[final_sz]{};
            for (int i = 0; i < final_sz; i++)
            {
                final_res[final_sz - i - 1] = res[s1 - i - 1];
            }
            delete[] res;
            UnlimitedInt *temp = new UnlimitedInt(final_res, final_sz, nsign, final_sz);
            delete[] final_res;
            return temp;
        }
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *current2 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), -1 * (i2->get_sign()), i2->get_size());
    UnlimitedInt *res = UnlimitedInt::add(i1, current2);
    delete current2;
    return res;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{   int sn1= i1->sign;
    int sn2 = i2->sign;
    int sz1 = i1->size;
    int sz2 = i2->size;                 
    int cap1 = i1->capacity;
    int cap2 = i2->capacity;
    int final_sign = sn1 * sn2;
    if (final_sign == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt();
        return temp;
    }
    else
    {
        int *num1;
        int *num2;
        int s1;
        int s2;
        if (i1->get_size() < i2->get_size())
        {   
            s1 = i2->get_size();
            s2 = i1->get_size();
            num1 = i2->get_array();
            num2 = i1->get_array();
        }
        else
        {   s1 = i1->get_size();
            s2 = i2->get_size();
            num1 = i1->get_array();
            num2 = i2->get_array();
            
        }
        int final_sz = s1 + s2;
        int *res = new int[final_sz]{};
        for (int i = s1 - 1; i >= 0; i--)
        {
            for (int j = s2 - 1; j >= 0; j--)
            {
                int mul = num1[i] * num2[j];
                int sum = mul + res[i + j + 1];

                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }

        for (int i = 0; i < s1 + s2; i++)
        {
            if (res[i] == 0)
            {
                final_sz--;
            }
            else
            {
                break;
            }
        }
        int *final_res = new int[final_sz]{};
        for (int i = 0; i < final_sz; i++)
        {
            final_res[final_sz - i - 1] = res[s1 + s2 - i - 1];
        }
        delete[] res;
        UnlimitedInt *temp = new UnlimitedInt(final_res, final_sz, final_sign, final_sz);
        delete[] final_res;
        return temp;
    }
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{   int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    int* num1 = i1->get_array();
    int* num2 = i2->get_array();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int final_sn = sign1 * sign2;
    
    if (final_sn == 0 || (is_bigger_mod(i1, i2) == -1 && final_sn == 1))
    {
        return new UnlimitedInt(); // No need for a temporary variable
    }
    else if (is_bigger_mod(i1, i2) == -1 && final_sn == -1)
    {
        return new UnlimitedInt(-1); // No need for a temporary variable
    }
    else
    {
        UnlimitedInt *curr1 = new UnlimitedInt(i1->get_array(), i1->get_size(), 1, i1->get_size());
        UnlimitedInt *curr2 = new UnlimitedInt(i2->get_array(), i2->get_size(), 1, i2->get_size());
        UnlimitedInt *rem = new UnlimitedInt();
        
        UnlimitedInt *ten = new UnlimitedInt(10);
        UnlimitedInt *temp;
        UnlimitedInt *current;
        UnlimitedInt *q = new UnlimitedInt();
        
        for (int i = 0; i < i1->get_size(); i++)
        {
            temp = rem;
            rem = UnlimitedInt::mul(temp, ten);
            delete temp;
            
            current = new UnlimitedInt(curr1->unlimited_int[i]);
            temp = rem;
            rem = UnlimitedInt::add(temp, current);
            delete temp;
            delete current;

            int x = 0;
            while (is_bigger_mod(rem, curr2) >= 0)
            {
                temp = rem;
                rem = UnlimitedInt::sub(temp, curr2);
                delete temp;
                x++;
            }
            
            temp = q;
            q = UnlimitedInt::mul(temp, ten);
            delete temp;
            
            temp = q;
            UnlimitedInt *faltu = new UnlimitedInt(x);
            q = UnlimitedInt::add(temp, faltu);
            delete temp;
            delete faltu;
        }
        
        delete ten;
        delete curr1;
        delete curr2;
        
        q->sign = final_sn;
        
        if (final_sn == -1 && rem->get_sign() == +1)
        {
            UnlimitedInt *tempo2 = new UnlimitedInt(1);
            UnlimitedInt *tempo = q;
            q = UnlimitedInt::sub(tempo, tempo2);
            delete tempo2;
            delete tempo;
        }
        
        delete rem;
        
        return q;
    }
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt* q = UnlimitedInt::div(i1,i2);
    UnlimitedInt* mult = UnlimitedInt::mul(q,i2);
    UnlimitedInt* mod = UnlimitedInt::sub(i1, mult);
    delete q;
    delete mult;
    return mod;
}

string UnlimitedInt::to_string(){
    string res = "";
    if (sign == 0){
        res = "0";
    }
    else{
        if (sign == -1){
            res = res + "-";
            for(int i = 0; i < size; i++){
            res = res + std::to_string(unlimited_int[i]);
        }
        }
        else{
    
        for(int i = 0; i < size; i++){
            res = res + std::to_string(unlimited_int[i]);
        }
        }
    }
    return res;
}