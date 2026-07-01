class Solution {
public:
    int n;
    vector<vector<int>> dist;
    vector<pair<int,int>> dir = {{1,0},{-1,0},{0,1},{0,-1}};

    void multiSourceBFS(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        dist.assign(n, vector<int>(n, INT_MAX));

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    dist[i][j]=0;
                    q.push({i,j});
                }
            }
        }

        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();

            for(auto [dx,dy]:dir){
                int nx=x+dx;
                int ny=y+dy;

                if(nx>=0 && ny>=0 && nx<n && ny<n &&
                   dist[nx][ny]==INT_MAX){

                    dist[nx][ny]=dist[x][y]+1;
                    q.push({nx,ny});
                }
            }
        }
    }

    bool canReach(int safe){
        if(dist[0][0] < safe) return false;

        queue<pair<int,int>> q;
        vector<vector<int>> vis(n, vector<int>(n,0));

        q.push({0,0});
        vis[0][0]=1;

        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();

            if(x==n-1 && y==n-1)
                return true;

            for(auto [dx,dy]:dir){
                int nx=x+dx;
                int ny=y+dy;

                if(nx>=0 && ny>=0 && nx<n && ny<n &&
                   !vis[nx][ny] &&
                   dist[nx][ny]>=safe){

                    vis[nx][ny]=1;
                    q.push({nx,ny});
                }
            }
        }

        return false;
    }

    int maximumSafenessFactor(vector<vector<int>>& grid) {

        n=grid.size();

        multiSourceBFS(grid);

        int low=0;
        int high=2*n;
        int ans=0;

        while(low<=high){

            int mid=(low+high)/2;

            if(canReach(mid)){
                ans=mid;
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }

        return ans;
    }
};