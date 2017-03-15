
//i节点的父节点 (i-1)/2, 左子节点2*i+1, 右子节点2*i+2,

/* 从子节点沿着父节点做插入排序，MaxHeap */
void maxHeapFixUp( int a[], i )
{
	int tmp = a[i];
	int j = (i - 1)/2;
	while( j >=0 && i != 0 )
	{
		if( a[j] < tmp )
		{
			a[i] = a[j];     //move the little down,
			i = j;
			j = (i - 1)/2;
		}
		else
		{
			break;
		}
	}
	a[i] = tmp;  //lay it on the final position
}

/* 插入数据为最表层,然后fixup */
void maxHeapInsert( int a[], int n, int num )
{
	a[n] = num;
	maxHeapFixUp( a, n );
}

/* 堆删除，只能删除根结点，然后fixdown, 从i开始调整，n为最大个数 */
void maxHeapFixDown( int a[], int i, int n )
{
	int tmp = a[i];
	int j = 2*i+1;
	
	while( j<n )
	{
		/*compare the left and right, take the biggest*/
		if( j+1<n && a[j+1]>a[j] )
		{
			j++;
		}
		
		if( a[j] <= tmp )
		{
			break; //end
		}
		
		//swap
		a[i] = a[j];  //move the bigger up
		i = j;
		j = 2*i+1;
	}
	
	a[i] = tmp; // lay it on the final positon
}

/* remove the root,swap it with the last one */
void maxHeapRemove( int a[], int n )
{
	swap(a[0], a[n-1]);
	maxHeapFixDown( a, 0, n-1 );
}

/* heap */
void maxHeapCreate( int a[], int n )
{
	int i = 0;
	for( i = (n-1 -1)/2; i >= 0; i-- )
	{
		maxHeapFixDown( a, i, n );
	}
}

/* maxHeap sort, ascend, n is the count of numbers in array */
void maxHeapSortAscend( int a[], int n )
{
	int i;
	
	maxHeapCreate( a, n );
	for( i = 0; i < n - 1; i++ )
	{
		swap( a[0], a[n-1-i] );
		maxHeapFixDown( a, o, n-1-i );
	}
}

void swap( int i, int j )
{
	int tmp = i;
	i = j;
	j = tmp;
}

//-------------------------
//LDR,中(根)序遍历,红黑树/平衡树，L < D < R
//DLR,前（先根）序遍历
//LRD,后序遍历


DLR_visit(root)
{
  prev = null;
	curr = root;
	
	while( curr != null )
	{
		print curr.value
		
		if( curr.left != null )
		{
			prev = curr;
			curr = curr.left;
		}
		else if( curr.right != null )
		{
			prev = curr;
			curr = curr.right;
		}
		else 
		{
		  //leaf node
		  curr = curr.parent;
		  while( curr )
		  {
		  	if( curr.right )
		  	{
					curr = curr.right;
					break;		  		
		  	}
		  	curr = curr.parent;
		  }
		}
	}
}


LDR_visit(root)
{
  prev = null;
  next = null;
	curr = root;
	
	while( curr != null )
	{	  
	  if ( prev == curr.parent )
	  {
	     prev = curr;
	     next = curr.left;
	  }
	  
	  if ( next == null || prev == curr.left )
	  {
	     print curr;
	     prev = curr;
	     next = curr.right;	     
	  }
	  
	  if( next == null || prev == curr.right )
	  {
	  	prev = curr;
	  	next = curr.parent;
	  }
	  
	  curr = next;
	}
}

LDR_visit(root)
{
   curr = root;
   prev = curr.parent;
   
   while( curr )
	 {
	   if( prev == curr.parent )
	   {
	     //find the left
	   		if( curr.left != null )
	   		{
	   		  prev = curr;
	   			curr = curr.left
	   		}
	   		else
	   		{
		   		//end, leaf
	   		   print curr;
	   		   prev = curr;
	   		   if ( curr.right != null )
	   		   {
	   		      curr = curr.right;
	   		   }
	   		   else
	   		   {
	   		   		curr = curr.parent;
	   		   }
   		   }
	   }
	   else if ( prev == curr.left )
	   {
	      //positon is D
	   		print curr;
	   		prev = curr;
   		   if ( curr.right != null )
   		   {
   		      curr = curr.right;
   		   }
   		   else
   		   {
   		   		curr = curr.parent;
   		   }
	   }
	   else if ( prev == curr.right )
	   {
	      //back to parent
	   		prev = curr;
	   		curr = curr.parent;
	   }
   }
}

LDR_visit(root)
{
	
}

quikSort( int a[], int begin, int end )
{
	int idx = end;
	int i = begin - 1;
	int j = begin;
	
	if( begin >= end )
		return;
		
	while( j < end )
	{
		if( a[j] < a[idx] )
		{
			i++;
			swap(a[j],a[i]);
		}
		j++;
	}
	
  swap(a[i+1],a[idx]);
  
  quikSort(a,begin, i);
  quiksort(a,i+2,end);
}

//assume k is big enought. ASC ording
void mergeSort( int a[], int begin, int end, int tmp[k] )
{
	
	int mid = (begin+end)/2;
	
	if( begin >= end )
		return;
		
		mergeSort( a, begin, mid );
		mergeSort( a, mid + 1, end );
		
		{
			//merge
			int i = begin;
			int j = mid+1;
			int t = 0;
			
			while( i <= mid && j <= end )
			{
				if( a[i] < a[j] )
					tmp[t++] = a[i++];
				else if( a[i] >= a[j] )
					tmp[t++] = a[j++];					
			}
			
			while( i <= mid )
				tmp[t++] = a[i++];
			while( j <= end )
			  tmp[t++] = a[j++];
			
			i = 0;
			j = begin;
			while( i < t )
				a[j++] = tmp[i++];
		}
}

//ASC order
void insertSort( int a[], int n )
{
	int i = 0;
	int j = 0;
	int value = 0;
	
	for( i = 1; i < n; i++ )
	{
		if( a[i] < a[i-1] )
		{
			value = a[i];
			j = i;
			
			while( j > 0 && value < a[j-1] )
			{
				a[j] = a[j-1];
				j--;
			}
			
			a[j] = value
		}
	}
}