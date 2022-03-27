#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

//��Ŀ�������������ǿյ�������ʾ�����Ǹ�������������ÿλ���ֶ��ǰ�������ķ�ʽ�洢�ģ�����ÿ���ڵ�ֻ�ܴ洢һλ����
//���㽫��������ӣ�������ͬ��ʽ����һ����ʾ�͵�����
//����Լ����������0֮�⣬����������������0��ͷ��

//����˼·һ��
//��Ϊ����������洢�ģ����Ծٸ�����2->3->4->0,��2340������������д洢��ʽΪ0->4->3->2;
//��9->5->8,��958������������д洢��ʽΪ8->5->9;
//��Ȼ2340+958=3298������ҲҪ����ͬ��ʽ��������ͣ���ͬ��������ʽ�洢�����������ֵΪ8923�����Կ�������������һ��ֵ��������1��һ��ֵ������2��һ��ֵ������ѧ�ӷ��õ��Ľ�λ������
//��������һ��ͷָ�룬ָ��ṹ��ListNode,������Ϊ* ListNode��ͬʱ����ֵΪ��ָ�룬����һ��βָ�룬ͬ��ָ��ṹ��ListNode,������Ϊ* ListNode,Ҳͬ������ֵΪ��ָ�롣
//��ͷָ�벻���ڣ����տ�ʼ��ʱ����head=tail=new ListNode(sum%10); ����sum=n1+n2+carry,n1=L1->val,n2=L2->val,carry�ĳ�ʼֵΪ0��Ϊ��λ���Ժ���ܻ���1�ġ�
//��ͷָ����ڣ�����һ�δ���(new)ListNode֮����tail->next= new ListNode(sum%10),tail=tail->next
//���һ��������λ��Ϊ0����Ϊ1�£�����Ҫ�ڽ�tail->next=new ListNode(carry) ,����head����


//�����Զ��������ڵ�ṹ��
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* L1, ListNode* L2)
    {
        ListNode* head = nullptr, *tail = head;
        int carry = 0;
        while (L1 || L2)
        {
            int n1 = L1 ? L1->val : 0;
            int n2 = L2 ? L2->val : 0;
            int sum = n1 + n2 + carry;
            if (!head)
            {
                head = tail = new ListNode(sum % 10);
            }
            else
            {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;

            }
            carry = sum / 10;
            if (L1)
            {
                L1 = L1->next;
            }
            if (L2)
            {
                L2 = L2->next;
            }
            
        }
        if (carry > 0)
        {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};

void test01()
{
    ListNode L1_4 = ListNode(2);
    ListNode L1_3 = ListNode(3, &L1_4);
    ListNode L1_2 = ListNode(4, &L1_3);
    ListNode L1 = ListNode(0, &L1_2);
    ListNode* L1temp = &L1;
    cout << "L1= ";
    for (int i = 0; i < 4; i++)
    {
        cout << L1temp->val;
        L1temp = L1temp->next;
    }
    cout << endl;
    ListNode L2_3 = ListNode(9);
    ListNode L2_2 = ListNode(5,&L2_3);
    ListNode L2 = ListNode(8, &L2_2);
    ListNode* L2temp = &L2;
    cout << "L2= ";
    for (int i = 0; i < 3; i++)
    {
        cout << L2temp->val;
        L2temp = L2temp->next;
    }
    cout << endl;
    Solution solution;
    ListNode *ret=solution.addTwoNumbers(&L1, &L2);
    cout << "ret=";
    for (int i = 0; i < 4; i++)
    {
        cout << ret->val;
        ret = ret->next;
    }
    cout << endl;
    cout << "��������8923����ȷ��" << endl;
}


//����˼·����
////����������洢�ģ��ٸ�����8->3->7,��837������������д洢��ʽΪ7->3->8;
//��5->6->4,��564������������д洢��ʽΪ4->6->5;
//��Ȼ837+564=1401������ҲҪ����ͬ��ʽ��������ͣ���ͬ��������ʽ�洢�����������ֵΪ1041�����Կ�������������һ��ֵ��������1��һ��ֵ������2��һ��ֵ������ѧ�ӷ��õ��Ľ�λ������
//��������һ��L3ָ�룬ָ��ṹ��ListNode,������Ϊ* ListNode��ͬʱ����ֵΪListNode(0),��ֵΪ0��nextΪ��ָ�룬����һ��L4ָ�룬ͬ��ָ��ṹ��ListNode,������Ϊ* ListNode,Ҳͬ������ֵΪListNode(0)��
//���ĵط��������һ�������sumtemp,����Ա�ʾÿһλ�ӷ�֮��ĺ�
//��L3��L4��sumtemp���ڣ���L4->next ָ��new ListNode(sumtemp%10),�����˳�
//��󷵻�L3->next����,��ΪL3��valΪ0,��next��ʼ��Ч����L3�洢�ĵڶ���������Ч��

class Solution2
{
public:
    ListNode* addTwoNumbers(ListNode* L1, ListNode* L2)
    {
        ListNode* L3 = new ListNode(0), * L4 = L3;
        int sumtemp = 0;
        while (L1 || L2 || sumtemp)
        {
            if (L1)
            {
                sumtemp += L1->val;
                L1 = L1->next;
            }
            if (L2)
            {
                sumtemp += L2->val;
                L2 = L2->next;
            }
            L4->next = new ListNode(sumtemp % 10);
            L4 = L4->next;
            sumtemp /= 10;
        }
        return L3->next;

    }
};

void test02()
{

    ListNode L1_3= ListNode(8);
    ListNode L1_2 = ListNode(3, &L1_3);
    ListNode L1 = ListNode(7, &L1_2);
    ListNode* L1temp = &L1;
    cout << "L1= ";
    for (int i = 0; i < 3; i++)
    {
        cout << L1temp->val;
        L1temp = L1temp->next;
    }
    cout << endl;
    ListNode L2_3 = ListNode(5);
    ListNode L2_2 = ListNode(6, &L2_3);
    ListNode L2 = ListNode(4, &L2_2);
    ListNode* L2temp = &L2;
    cout << "L2= ";
    for (int i = 0; i < 3; i++)
    {
        cout << L2temp->val;
        L2temp = L2temp->next;
    }
    cout << endl;
    Solution solution2;
    ListNode* ret = solution2.addTwoNumbers(&L1, &L2);
    cout << "ret=";
    for (int i = 0; i < 4; i++)
    {
        cout << ret->val;
        ret = ret->next;
    }
    cout << endl;
    cout << "��������1041����ȷ��" << endl;
}









int main() {

    test01();
    cout << "---------�������ֽⷨ�Ļ����ָ���--------------" << endl;
    test02();
	system("pause");
	return 0;
}
