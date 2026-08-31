class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> criticalPos;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int pos = 2; // current node position

        while (curr && curr->next) {
            bool isMax = (curr->val > prev->val &&
                          curr->val > curr->next->val);

            bool isMin = (curr->val < prev->val &&
                          curr->val < curr->next->val);

            if (isMax || isMin) {
                criticalPos.push_back(pos);
            }

            prev = curr;
            curr = curr->next;
            pos++;
        }

        if (criticalPos.size() < 2)
            return {-1, -1};

        int minDist = INT_MAX;

        for (int i = 1; i < criticalPos.size(); i++) {
            minDist = min(minDist,
                          criticalPos[i] - criticalPos[i - 1]);
        }

        int maxDist = criticalPos.back() - criticalPos.front();

        return {minDist, maxDist};
    }
};