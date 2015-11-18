bool cmp(int a,int b)
{
    return a > b;
}
class MedianFinder
{
	public:
		vector<int> minHeap;
		vector<int> maxHeap;
	public:
		MedianFinder()
		{
			make_heap(minHeap.begin(),minHeap.end(),cmp);
			make_heap(maxHeap.begin(),maxHeap.end());
		}

		void addNum(int num)
		{
			if(maxHeap.size() > minHeap.size())
			{
				minHeap.push_back(num);
				push_heap(minHeap.begin(),minHeap.end(),cmp);

			}
			else if(maxHeap.size() == minHeap.size())
			{
				maxHeap.push_back(num);
				push_heap(maxHeap.begin(),maxHeap.end());
			}
			if(maxHeap.size() >0 && minHeap.size() > 0 && maxHeap[0] > minHeap[0])
			{
			    int max = maxHeap[0];
			    int min = minHeap[0];

			    pop_heap(maxHeap.begin(),maxHeap.end());
			    maxHeap.pop_back();

			    maxHeap.push_back(min);
			    push_heap(maxHeap.begin(),maxHeap.end());

			    pop_heap(minHeap.begin(),minHeap.end(),cmp);
			    minHeap.pop_back();

			    minHeap.push_back(max);
			    push_heap(minHeap.begin(),minHeap.end(),cmp);
			}

		}

		double findMedian()
		{
			if(maxHeap.size() == minHeap.size())
			{
				return (maxHeap[0]+minHeap[0])/2.0;
			}
			else return maxHeap[0];
		}
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
