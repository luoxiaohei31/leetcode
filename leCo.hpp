#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<unordered_map>
#include<unordered_set>


namespace lxj{
    /****************************数据结构部分*******************************/

    //数据结构：链表
    struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };


    /**********************************************************************/


    /*****************************算法部分**********************************/
    /******************在数 1~(n-1) 之间，找出所有组合，其元素相加总和为 n *********************************/
    /*
    给定一个正整数m，将其分解为多个数组[a1,a2,...,an]，数组和Sn=m，且an>a(n-1),a1>=1
    比如m=10，可分解为[1,9]/[1,2,3,4]/[2,3,5]
    */
    std::vector<std::vector<int>> valueDecom(int startIndex, int endIndex){
        std::vector<std::vector<int>> vvi;
        std::stack<int> memoryStack, resolveStack;

        auto tfs=[](std::stack<int> si){
            std::stack<int> tfStack;
            while(!si.empty()){
                tfStack.push(si.top());
                si.pop();
            }
            return tfStack;
        };

        memoryStack.push(startIndex);
        int curDIF=endIndex;
        while((memoryStack.top()+1)*2 <= curDIF){
            std::stack<int> transferStack=tfs(memoryStack);
            std::vector<int> vi;
            while(!transferStack.empty()){
                vi.push_back(transferStack.top());
                transferStack.pop();
            }
            
            curDIF-=memoryStack.top();
            memoryStack.push(memoryStack.top()+1);
            vi.push_back(curDIF);
            vvi.push_back(vi);
        }

        if(memoryStack.size()>1)    memoryStack.pop();
        resolveStack.push(curDIF);

        auto stackSum=[](std::stack<int> si)mutable{
            int sum=0;
            while(!si.empty()){
                sum+=si.top();
                si.pop();
            }
            return sum;
        };

        int memoryNum=memoryStack.top();
        while(!memoryStack.empty()){
            int resolveSum=stackSum(resolveStack);
            int a=memoryNum+1;
            int b=resolveSum-a;
            if(memoryStack.top()+1 >= (resolveSum-memoryStack.top()-1)){
                resolveStack.pop();
                resolveStack.push(resolveSum+memoryStack.top());
                memoryStack.pop();
                continue;
            }
            if(a >= b){
                while(!resolveStack.empty()){
                    resolveStack.pop();
                }
                resolveStack.push(resolveSum+memoryStack.top());
                memoryNum=memoryStack.top();
                memoryStack.pop();
                continue;
            }
            resolveStack.pop();
            resolveStack.push(b);
            memoryStack.push(a);
            memoryNum=memoryStack.top();

            std::stack<int> transferStack=tfs(memoryStack);
            std::vector<int> vi;
            while(!transferStack.empty()){
                vi.push_back(transferStack.top());
                transferStack.pop();
            }
            vi.push_back(resolveStack.top());
            vvi.push_back(vi);
        }

        return vvi;
    }

    const std::vector<std::vector<int>> getWay(int runCount){
        std::vector<std::vector<int>> mainVec;
        mainVec.reserve(runCount);

        for(int i=1; i<runCount/2+1; ++i){
            auto vvi=valueDecom(i, runCount);
            std::move(vvi.begin(),vvi.end(),std::back_inserter(mainVec));
        }

        return mainVec;
    }
    /****************************************************************************************************/

    //在数组[1,2,3,4,5,6,7,8,9]中每三个元素组合为一个数字，使它们的比例为1:2:3
    const std::vector<std::vector<int>> combiVec(){
        std::set<int> setI;
        auto decoK=[&setI](int k){
            if(k<10)    return;

            int rema=0;
            for(int i=1; i!=1000; i*=10){
                rema=(k%(i*10)-rema)/i;
                setI.insert(rema);
            }
        };

        auto decoI=[](int i){
            if(i<100)    return std::stack<int>{};

            std::stack<int> stackI;
            int rema=0;
            for(int a=1; a!=1000; a*=10){
                rema=(i%(a*10)-rema)/a;
                stackI.push(rema);
            }

            return stackI;
        };

        std::vector<std::vector<int>> vvi;
        std::vector<int> vi;

        for(int k=987; k>=369; k--){
            if(k%10==0) continue;
            decoK(k);
            if(setI.find(0)!=setI.end()){
                setI.clear();
                continue;
            }
            int i=k%3==0 ? k/3 : 0;
            int j=i!=0 ? i*2 : 0;

            if(i==0  || j==0 || j%10==0){
                setI.clear();
                continue;
            }
            auto si=decoI(i);
            while(!si.empty()){
                int t=si.top();
                si.pop();
                if(setI.find(t)!=setI.end()) continue;
                setI.insert(t);
            }
            si=decoI(j);
            while(!si.empty()){
                int t=si.top();
                si.pop();
                if(setI.find(t)!=setI.end()) continue;
                setI.insert(t);
            }

            if(setI.size()!=9 || setI.find(0)!=setI.end()){
                setI.clear();
                continue;
            }

            vi.push_back(i);
            vi.push_back(j);
            vi.push_back(k);
            vvi.push_back(vi);
            vi.clear();
            setI.clear();
        }

        return vvi;
    }

    //有序数组的二分查找法(返回所找元素的下标)
    const int binarySearch(const std::vector<int>& vi,const int target){
        unsigned short left=0;
        unsigned short right=vi.size()-1;

        while(left<right){
            unsigned short middle=(left+right)/2;
            if(vi[middle]>target)
                right=middle;
            else if(vi[middle]<target)
                left=middle+1;
            else
                return middle;
        }

        return vi[left]==target ? left:-1;
    }

    //有序数组的平方
    /*给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序*/
    /*
    示例 1：
        输入：nums = [-4,-1,0,3,10]
        输出：[0,1,9,16,100]
        解释：平方后，数组变为 [16,1,0,9,100]
        排序后，数组变为 [0,1,9,16,100]
    */
   const std::vector<int> sortedSquares(const std::vector<int>& nums){
        unsigned short left=0;
        unsigned short right=nums.size()-1;

        std::vector<int> vi(nums.size());
        int i=nums.size()-1;
        while(i!=-1){
            if( std::pow(nums[left],2)>=std::pow(nums[right],2) ){
                vi[i--]=nums[left]*nums[left];
                left++;
            }
            else{
                vi[i--]=nums[right]*nums[right];
                right--;
            }
        }

        return vi;
   }


    //209. 长度最小的子数组
    /*给定一个含有 n 个正整数的数组和一个正整数 target 。
    找出该数组中满足其总和大于等于 target 的长度最小的 连续
    子数组[numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
    
    示例 1：
        输入：target = 7, nums = [2,3,1,2,4,3]
        输出：2
        解释：子数组 [4,3] 是该条件下的长度最小的子数组。
    */
   const int minSubArrayLen(int target, const std::vector<int>& nums) {
        int i=0;
        int result=INT_MAX;
        int sum=0;
        for(int j=0; j<nums.size(); j++){
            sum+=nums[j];
            while(sum>=target){
                int subLen=j-i+1;
                result=std::min(result,subLen);
                sum-=nums[i];
                i++;
            }
        }

        return result==INT_MAX ? 0:result;
    }

    //59. 螺旋矩阵 II
    /*
    给你一个正整数 n ，生成一个包含 1 到 n^2 的所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
    */
    const std::vector<std::vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> vvi(n);
        for(auto &vi:vvi)
            vi.resize(n);

        unsigned short LeftX=0,RightX=n-1;
        unsigned short TopY=0,BottomY=n-1;
        short number=1;
        while(LeftX<(n/2)){
            for(int j=LeftX; j!=RightX; j++){
                vvi[TopY][j]=number++;
            }
            for(int i=TopY; i!=BottomY; i++){
                vvi[i][RightX]=number++;
            }
            for(int j=RightX; j!=LeftX; j--){
                vvi[BottomY][j]=number++;
            }
            for(int i=BottomY; i!=TopY; i--){
                vvi[i][LeftX]=number++;
            }
            LeftX++;    RightX--;
            TopY++;     BottomY--;
        }
        if(n%2!=0)  vvi[LeftX][TopY]=number++;

        return vvi;
    }

    //203. 移除链表元素
    /*给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。*/
    const ListNode* removeElements(ListNode* head, int val) {
        if(head==nullptr)   return nullptr;

        auto p1=head;
        auto p=p1->next;
        for(; p!=nullptr;){
            while(p!=nullptr && p->val==val){
                auto removeNode=p;
                p1->next=p->next;
                p=p->next;
                delete removeNode;
            }
            p1=p1->next;
            p=(p==nullptr) ? p:p->next;
        }
        auto newHead=head->val==val ? head->next : head;
        head->val==val ? delete head : void();
        return newHead;
    }

    //707. 设计链表
    struct MyLinkedList{
        lxj::ListNode* head;
        lxj::ListNode* tail;

        MyLinkedList():head(new lxj::ListNode{0}), tail(nullptr){head->next=tail;}
        MyLinkedList(const std::initializer_list<int>& il):head(new lxj::ListNode{0}),tail(nullptr){
            auto cur=head;
            for(auto i:il){
                cur->next=new lxj::ListNode{i};
                cur=cur->next;
            }
            cur->next=tail;
        }
        
        int get(int index) {
            int val=-1;
            auto cur=head->next;
            while(index-- && cur!=tail){
                cur=cur->next;
            }

            val=cur==tail ? val:cur->val;
            return val;
        }
        
        void addAtHead(int val) {
            this->addAtIndex(0,val);
        }
        
        void addAtTail(int val) {
            auto cur=head;
            while(cur->next!=tail){
                cur=cur->next;
            }
            cur->next=new lxj::ListNode{val};
            cur->next->next=tail;
        }
        
        void addAtIndex(int index, int val) {
            auto cur=head;
            for(int i=0; i<index && cur!=nullptr; i++){
                cur=cur->next;
            }
            if(cur==nullptr)    return;
            auto next=cur->next;
            cur->next=new lxj::ListNode{val};
            cur->next->next=next;
        }
        
        void deleteAtIndex(int index) {
            if(index<0) return;
            auto cur=head;
            while(index>0 && cur!=tail){
                cur=cur->next;
                index--;
            }
            if(cur==tail || cur->next==tail)    return;
            auto delNode=cur->next;
            cur->next=delNode->next;
            delete delNode;
            delNode=nullptr;
        }
    };

    //206. 反转链表
    const ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr)    return head;
        lxj::ListNode* tail=nullptr;
        auto cur=head;
        auto next=cur->next;
        while(next!=nullptr){
            cur->next=tail;
            tail=cur;
            cur=next;
            next=next->next;
        }

        cur->next=tail;
        return cur;
    }

    //24. 两两交换链表中的节点
    /*给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题
    （即，只能进行节点交换）。*/
    const ListNode* swapPairs(ListNode* head) {
        if(head==nullptr || head->next==nullptr)    return head;

        lxj::ListNode* dummyHead=new lxj::ListNode(0,head);
        auto pre=dummyHead;

        while(head && head->next){
            pre->next=head->next;
            auto pro=head->next->next;
            head->next->next=head;
            head->next=pro;

            pre=head;
            head=pro;
        }

        auto newHead=dummyHead->next;
        delete dummyHead;
        dummyHead=nullptr;

        return newHead;
    }

    //19. 删除链表的倒数第 N 个结点
    /*给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。*/
    const ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head==nullptr)   return head;

        auto slowPtr=head;
        auto fastPtr=head;
        n+=1;

        while(n-- && fastPtr!=nullptr){
            fastPtr=fastPtr->next;
        }
        while(fastPtr!=nullptr){
            slowPtr=slowPtr->next;
            fastPtr=fastPtr->next;
        }

        auto delNode=slowPtr->next;
        slowPtr->next=slowPtr->next->next;
        delete delNode;
        delNode=nullptr;

        return head;
    }

    //142. 环形链表 II
    /*给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。*/
    const ListNode *detectCycle(ListNode *head) {
        if(head==nullptr || head->next==nullptr)    return nullptr;

        auto slowPtr=head->next, fastPtr=head->next->next;
        while(fastPtr!=nullptr && fastPtr->next!=nullptr && slowPtr!=fastPtr){
            fastPtr=fastPtr->next->next;
            slowPtr=slowPtr->next;
        }

        auto cur=head;
        if(slowPtr==fastPtr && fastPtr!=nullptr){
            while(cur!=slowPtr){
                cur=cur->next;
                slowPtr=slowPtr->next;
            }
            return cur;
        }

        return nullptr;
    }

    //160. 相交链表
    /*给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。*/
    const ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

        unsigned short lenA=0, lenB=0;
        auto cur1=headA, cur2=headB;
        while(cur1!=nullptr){
            cur1=cur1->next;
            lenA++;
        }
        while(cur2!=nullptr){
            cur2=cur2->next;
            lenB++;
        }
        
        cur1=lenA>=lenB ? headA:headB;      //cur1表示长链表的头
        cur2=cur1==headA ? headB:headA;     //cur2表示短链表的头
        unsigned short diff=std::abs(lenA-lenB);
        while(diff--){
            cur1=cur1->next;
        }

        while(cur1!=cur2 && cur2!=nullptr){
            cur1=cur1->next;
            cur2=cur2->next;
        }

        return cur2;
    }

    //242. 有效的字母异位词
    /*给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
    注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。*/
    const bool isAnagram(std::string s, std::string t) {
        int record[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            record[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            record[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (record[i] != 0) {
                return false;
            }
        }
        return true;
    }

    //349. 两个数组的交集
    /*给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。*/
    const std::vector<int> intersection(const std::vector<int>& nums1, const std::vector<int>& nums2) {
        std::unordered_set<int> findNums(nums1.begin(),nums1.end());
        std::unordered_set<int> result;

        for(int i=0; i!=nums2.size(); i++){
            if(findNums.find(nums2[i])!=findNums.end())
                result.insert(nums2[i]);
        }

        return std::vector<int>(result.begin(),result.end());
    }

    //454. 四数相加 II
    /*给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，请你计算有多少个元组 (i, j, k, l) 能满足：

    0 <= i, j, k, l < n
    nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
    */
    const int fourSumCount(const std::vector<int>& nums1, const std::vector<int>& nums2, 
                           const std::vector<int>& nums3, const std::vector<int>& nums4) {
        std::unordered_map<int,int> u_map;
        for(auto a:nums1){
            for(auto b:nums2){
                u_map[a+b]++;
            }
        }

        unsigned int count=0;
        for(auto c:nums3){
            for(auto d:nums4){
                int target=0-(c+d);
                if(u_map.find(target)!=u_map.end())
                    count+=u_map[target];
            }
        }

        return count;
    }

    //15. 三数之和
    /*给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 
    满足 i != j、i != k 且 j != k ，
    同时还满足 nums[i] + nums[j] + nums[k] == 0 。
    请你返回所有和为 0 且不重复的三元组。*/
    const std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        
        std::sort(nums.begin(),nums.end());
        for(int i=0; i!=nums.size(); i++){
            if(nums[i]>0)   return result;

            if(i>0 && nums[i]==nums[i-1])   continue;

            unsigned int left=i+1;
            unsigned int right=nums.size()-1;
            while(left<right){
                if(nums[i]+nums[left]+nums[right]>0){
                    right--;
                }
                else if(nums[i]+nums[left]+nums[right]<0){
                    left++;
                }
                else{
                    result.push_back(std::vector{nums[i],nums[left],nums[right]});
                    while(left<right && nums[right]==nums[right-1]) right--;
                    while(left<right && nums[left]==nums[left+1])   left++;

                    right--;
                    left++;
                }
            }
        }

        return result;
    }

    //202. 快乐数
    /*编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」 定义为：

    对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
    然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
    如果这个过程 结果为 1，那么这个数就是快乐数。

    如果 n 是 快乐数 就返回 true ；不是，则返回 false 。*/
    const bool isHappy(int n) {
        
        auto f=[](int a){
            unsigned int sum=0;
            while(a>=1){
                unsigned int i=a%10;
                sum+=i*i;
                a=a/10;
            }
            return sum;
        };

        unsigned int fast=n, slow=n;
        do{
            slow=f(slow);
            fast=f(fast);
            fast=f(fast);
        }while(slow!=fast);

        return slow==1;
    }

    //383. 赎金信
    /*给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。

    如果可以，返回 true ；否则返回 false 。

    magazine 中的每个字符只能在 ransomNote 中使用一次。*/
    const bool canConstruct(const std::string &ransomNote, const std::string &magazine) {
        std::unordered_map<char, int> r_map, m_map;
        for(char c: ransomNote){
            r_map[c]++;
        }
        for(char c:magazine){
            m_map[c]++;
        }

        for(auto p=r_map.begin(); p!=r_map.end(); p++){
            char c=(*p).first;
            if(m_map.find(c)==m_map.end()){
                return false;
            }
            else if((m_map[c]-r_map[c])<0){
                return false;
            }
            else{
                continue;
            }
        }

        return true;
    }

}

namespace testFunc{
    lxj::ListNode* setLinkList(const std::initializer_list<int>& il){
        lxj::ListNode* head=new lxj::ListNode{*il.begin()};
        auto cur=head;
        for(int i=1; i!=il.size(); i++){
            cur->next=new lxj::ListNode{*(il.begin()+i)};
            cur=cur->next;
        }
        return head;
    }
}