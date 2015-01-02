/* This is a buffer library created by Noah Huber-Feely
With it items can be easily added and removed, and it
supports all data types and buffer sizes.
To create a buffer object the syntax is Buffer<_chosenDataType, _size> _nameOfBuffer.
It is provided under the Mozilla Public License Version 2.0
*/

template<class T, int size>
class Buffer
{
private:
	int completeSize;
	T buffer[size];
	float backup;
	void moveAllOneUp();
	void moveAllOneDown();
	void moveUpToPoint(int depth);
	void moveDownFromPoint(int depth);
	int currentDepth;
public:
	Buffer();
	bool addToBuffer(T addition);
	bool addToFront(T addition);
	T popFirst();
	int currentAvailable();
	int percentageFull();
	T popItem(int depth);
	void flushBuffer();
	T returnBackup();
};

template<class T, int size>
Buffer<T, size>::Buffer()
{
	completeSize = size;
}

template<class T, int size>
bool Buffer< T, size>::addToBuffer(T addition)
{
	currentDepth++;
	if( currentDepth < completeSize)
	{
		buffer[currentDepth] = addition;
		return true;
	}
	else
	{
		backup = addition;
		currentDepth--;
		return false;
	}
}

template<class T, int size>
bool Buffer< T, size>::addToFront(T addition)
{
	currentDepth++;
	if( currentDepth < completeSize )
	{
		moveAllOneDown();
		buffer[0] = addition;
		return true;
	}
	else
	{
		backup = addition;
		currentDepth--;
		return false;
	}
}

template<class T, int size>
void Buffer< T, size>::flushBuffer()
{
	for(int i = currentDepth; i >= 0; i--)
	{
		buffer[i] = 0;
	}
	currentDepth = -1;
}

template<class T, int size>
int Buffer< T, size>::percentageFull()
{
	return (currentDepth / completeSize) * 100;
}

template<class T, int size>
int Buffer< T, size>::currentAvailable()
{
	return completeSize - currentDepth - 1;
}

template<class T, int size>
T Buffer< T, size>::popFirst()
{
	T save = buffer[0];
	buffer[0] = 0;
	moveAllOneUp();
	return save;
}

template<class T, int size>
T Buffer< T, size>::popItem(int depth)
{
	T save = buffer[depth];
	buffer[depth] = 0;
	moveUpToPoint(depth);
	return save;
}

template<class T, int size>
void Buffer< T, size>::moveAllOneUp()
{
	for(int i = 0; i >= currentDepth ; i++)
	{
		buffer[i - 1] = buffer[i];
	}
	buffer[currentDepth] = 0;
	currentDepth--;
}

template<class T, int size>
void Buffer< T, size>::moveDownFromPoint(int depth)
{
	for(int i = currentDepth; i >= depth; i--)
	{
		buffer[i + 1] = buffer[i];
		buffer[i] = 0.0;
	}
	currentDepth++;
}

template<class T, int size>
void Buffer< T, size>::moveUpToPoint(int depth)
{
}

template<class T, int size>
void Buffer< T, size>::moveAllOneDown()
{
}

template<class T, int size>
T Buffer< T, size>::returnBackup()
{
	return backup;
}
