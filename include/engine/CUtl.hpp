//
// Created by ENDERZOMBI102 on 01/03/2022.
//

#pragma once

#include <cstddef>
#include <algorithm>

#ifndef _WIN32
	#define __cdecl __attribute__((__cdecl__))
#endif

#define Assert(a) ( (void) 0 )

#define UTLMEMORY_TRACK_ALLOC() ( (void) 0 )
#define UTLMEMORY_TRACK_FREE() ( (void) 0 )
#define MEM_ALLOC_CREDIT_CLASS() ( (void) 0 )

template<class T> struct CUtlReference {
	CUtlReference* m_pNext;
	CUtlReference* m_pPrev;
	T* m_pObject;
};
template<class T> struct CUtlIntrusiveList {
	T* m_pHead;
};
template<class T> struct CUtlIntrusiveDList : public CUtlIntrusiveList<T> {};
template<class T> struct CUtlReferenceList : public CUtlIntrusiveDList< CUtlReference<T> > {};


template <class T, class I = int>
class CUtlMemory {
public:
	CUtlMemory(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemory(T* pMemory, int numElements);
	CUtlMemory(const T* pMemory, int numElements);
	~CUtlMemory();
	void Init(int nGrowSize = 0, int nInitSize = 0);

	class Iterator_t {
	public:
		Iterator_t(I i) : index(i) {
		}
		I index;

		bool operator==(const Iterator_t it) const { return index == it.index; }
		bool operator!=(const Iterator_t it) const { return index != it.index; }
	};

	Iterator_t First() const { return Iterator_t(IsIdxValid(0) ? 0 : InvalidIndex()); }
	Iterator_t Next(const Iterator_t& it) const { return Iterator_t(IsIdxValid(it.index + 1) ? it.index + 1 : InvalidIndex()); }
	I GetIndex(const Iterator_t& it) const { return it.index; }
	bool IsIdxAfter(I i, const Iterator_t& it) const { return i > it.index; }
	bool IsValidIterator(const Iterator_t& it) const { return IsIdxValid(it.index); }
	Iterator_t InvalidIterator() const { return Iterator_t(InvalidIndex()); }
	T& operator[](I i);
	const T& operator[](I i) const;
	T& Element(I i);
	const T& Element(I i) const;
	bool IsIdxValid(I i) const;
	static I InvalidIndex() { return (I)-1; }
	T* Base();
	const T* Base() const;
	void SetExternalBuffer(T* pMemory, int numElements);
	void SetExternalBuffer(const T* pMemory, int numElements);
	void AssumeMemory(T* pMemory, int nSize);
	// void Swap(CUtlMemory<T, I>& mem);
	void ConvertToGrowableMemory(int nGrowSize);
	int NumAllocated() const;
	int Count() const;
	void Grow(int num = 1);
	void EnsureCapacity(int num);
	void Purge();
	void Purge(int numElements);
	bool IsExternallyAllocated() const;
	bool IsReadOnly() const;
	void SetGrowSize(int size);

protected:
	void ValidateGrowSize() {
	}

	enum {
		EXTERNAL_BUFFER_MARKER = -1,
		EXTERNAL_CONST_BUFFER_MARKER = -2,
	};

	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template <class T, class A = CUtlMemory<T>>
class CUtlVector {
	typedef A CAllocator;

public:
	typedef T ElemType_t;

	CUtlVector(int growSize = 0, int initSize = 0);
	CUtlVector(T* pMemory, int allocationCount, int numElements = 0);
	~CUtlVector();
	CUtlVector<T, A>& operator=(const CUtlVector<T, A>& other);
	T& operator[](int i);
	const T& operator[](int i) const;
	T& Element(int i);
	const T& Element(int i) const;
	T& Head();
	const T& Head() const;
	T& Tail();
	const T& Tail() const;
	T* Base() { return m_Memory.Base(); }
	const T* Base() const { return m_Memory.Base(); }
	int Count() const;
	int Size() const;
	bool IsValidIndex(int i) const;
	static int InvalidIndex();
	int AddToHead();
	int AddToTail();
	int InsertBefore(int elem);
	int InsertAfter(int elem);
	int AddToHead(const T& src);
	int AddToTail(const T& src);
	int InsertBefore(int elem, const T& src);
	int InsertAfter(int elem, const T& src);
	int AddMultipleToHead(int num);
	int AddMultipleToTail(int num, const T* pToCopy = NULL);
	int InsertMultipleBefore(int elem, int num, const T* pToCopy = NULL);
	int InsertMultipleAfter(int elem, int num);
	void SetSize(int size);
	void SetCount(int count);
	void CopyArray(const T* pArray, int size);
	// void Swap(CUtlVector<T, A>& vec);
	int AddVectorToTail(CUtlVector<T, A> const& src);
	int Find(const T& src) const;
	bool HasElement(const T& src) const;
	void EnsureCapacity(int num);
	void EnsureCount(int num);
	void FastRemove(int elem);
	void Remove(int elem);
	bool FindAndRemove(const T& src);
	void RemoveMultiple(int elem, int num);
	void RemoveAll();
	void Purge();
	void PurgeAndDeleteElements();
	void Compact();
	void SetGrowSize(int size) { m_Memory.SetGrowSize(size); }
	int NumAllocated() const;
	void Sort(int(__cdecl* pfnCompare)(const T*, const T*));

protected:
	//CUtlVector(CUtlVector const& vec) { Assert(0); }
	void GrowVector(int num = 1);
	void ShiftElementsRight(int elem, int num = 1);
	void ShiftElementsLeft(int elem, int num = 1);

	CAllocator m_Memory;
	int m_Size;
	T* m_pElements;

	inline void ResetDbgInfo() { m_pElements = Base(); }
};

template <typename T, class A>
inline CUtlVector<T, A>::CUtlVector(int growSize, int initSize)
		: m_Memory(growSize, initSize) , m_Size(0) {
	ResetDbgInfo();
}

template <typename T, class A>
inline CUtlVector<T, A>::CUtlVector(T* pMemory, int allocationCount, int numElements)
		: m_Memory(pMemory, allocationCount) , m_Size(numElements) {
	ResetDbgInfo();
}

template <typename T, class A>
inline CUtlVector<T, A>::~CUtlVector() {
	Purge();
}

template <typename T, class A>
inline CUtlVector<T, A>& CUtlVector<T, A>::operator=(const CUtlVector<T, A>& other) {
	int nCount = other.Count();
	SetSize(nCount);
	for (int i = 0; i < nCount; i++) {
		(*this)[i] = other[i];
	}
	return *this;
}

template <typename T, class A>
inline T& CUtlVector<T, A>::operator[](int i) {
	return m_Memory[i];
}

template <typename T, class A>
inline const T& CUtlVector<T, A>::operator[](int i) const {
	return m_Memory[i];
}

template <typename T, class A>
inline T& CUtlVector<T, A>::Element(int i) {
	return m_Memory[i];
}

template <typename T, class A>
inline const T& CUtlVector<T, A>::Element(int i) const {
	return m_Memory[i];
}

template <typename T, class A>
inline T& CUtlVector<T, A>::Head() {
	Assert(m_Size > 0);
	return m_Memory[0];
}

template <typename T, class A>
inline const T& CUtlVector<T, A>::Head() const {
	Assert(m_Size > 0);
	return m_Memory[0];
}

template <typename T, class A>
inline T& CUtlVector<T, A>::Tail() {
	Assert(m_Size > 0);
	return m_Memory[m_Size - 1];
}

template <typename T, class A>
inline const T& CUtlVector<T, A>::Tail() const {
	Assert(m_Size > 0);
	return m_Memory[m_Size - 1];
}

template <typename T, class A>
inline int CUtlVector<T, A>::Size() const {
	return m_Size;
}

template <typename T, class A>
inline int CUtlVector<T, A>::Count() const {
	return m_Size;
}

template <typename T, class A>
inline bool CUtlVector<T, A>::IsValidIndex(int i) const {
	return (i >= 0) && (i < m_Size);
}

template <typename T, class A>
inline int CUtlVector<T, A>::InvalidIndex() {
	return -1;
}

template <typename T, class A>
void CUtlVector<T, A>::GrowVector(int num) {
	if ( m_Size + num > m_Memory.NumAllocated() ) {
		MEM_ALLOC_CREDIT_CLASS();
		m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());
	}

	m_Size += num;
	ResetDbgInfo();
}

template <typename T, class A>
void CUtlVector<T, A>::Sort( int(__cdecl* pfnCompare)(const T*, const T*) ) {
	typedef int(__cdecl * QSortCompareFunc_t)(const void*, const void*);
	if (Count() <= 1)
		return;

	if (Base()) {
		qsort(Base(), Count(), sizeof(T), (QSortCompareFunc_t)(pfnCompare));
	} else {
		Assert(0);

		for (int i = m_Size - 1; i >= 0; --i) {
			for (int j = 1; j <= i; ++j) {
				if (pfnCompare(&Element(j - 1), &Element(j)) < 0) {
					swap(Element(j - 1), Element(j));
				}
			}
		}
	}
}

template <typename T, class A>
void CUtlVector<T, A>::EnsureCapacity(int num) {
	MEM_ALLOC_CREDIT_CLASS();
	m_Memory.EnsureCapacity(num);
	ResetDbgInfo();
}

template <typename T, class A>
void CUtlVector<T, A>::EnsureCount(int num) {
	if (Count() < num)
		AddMultipleToTail(num - Count());
}

template <typename T, class A>
void CUtlVector<T, A>::ShiftElementsRight(int elem, int num) {
	Assert(IsValidIndex(elem) || (m_Size == 0) || (num == 0));
	int numToMove = m_Size - elem - num;
	if ((numToMove > 0) && (num > 0))
		memmove(&Element(elem + num), &Element(elem), numToMove * sizeof(T));
}

template <typename T, class A>
void CUtlVector<T, A>::ShiftElementsLeft(int elem, int num) {
	Assert(IsValidIndex(elem) || (m_Size == 0) || (num == 0));
	int numToMove = m_Size - elem - num;
	if ((numToMove > 0) && (num > 0)) {
		memmove(&Element(elem), &Element(elem + num), numToMove * sizeof(T));
	}
}

template <typename T, class A>
inline int CUtlVector<T, A>::AddToHead() {
	return InsertBefore(0);
}

template <typename T, class A>
inline int CUtlVector<T, A>::AddToTail() {
	return InsertBefore(m_Size);
}

template <typename T, class A>
inline int CUtlVector<T, A>::InsertAfter(int elem) {
	return InsertBefore(elem + 1);
}

template <typename T, class A>
int CUtlVector<T, A>::InsertBefore(int elem) {
	Assert((elem == Count()) || IsValidIndex(elem));

	GrowVector();
	ShiftElementsRight(elem);
	Construct(&Element(elem));
	return elem;
}

template <typename T, class A>
inline int CUtlVector<T, A>::AddToHead(const T& src) {
	Assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));
	return InsertBefore(0, src);
}

template <typename T, class A>
inline int CUtlVector<T, A>::AddToTail(const T& src) {
	Assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));
	return InsertBefore(m_Size, src);
}

template <typename T, class A>
inline int CUtlVector<T, A>::InsertAfter(int elem, const T& src) {
	Assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));
	return InsertBefore(elem + 1, src);
}

template <typename T, class A>
int CUtlVector<T, A>::InsertBefore(int elem, const T& src) {
	Assert((Base() == NULL) || (&src < Base()) || (&src >= (Base() + Count())));

	Assert((elem == Count()) || IsValidIndex(elem));

	GrowVector();
	ShiftElementsRight(elem);
	CopyConstruct(&Element(elem), src);
	return elem;
}

template <typename T, class A>
inline int CUtlVector<T, A>::AddMultipleToHead(int num) {
	return InsertMultipleBefore(0, num);
}

template <typename T, class A>
inline int CUtlVector<T, A>::AddMultipleToTail(int num, const T* pToCopy) {
	Assert((Base() == NULL) || !pToCopy || (pToCopy + num < Base()) || (pToCopy >= (Base() + Count())));

	return InsertMultipleBefore(m_Size, num, pToCopy);
}

template <typename T, class A>
int CUtlVector<T, A>::InsertMultipleAfter(int elem, int num) {
	return InsertMultipleBefore(elem + 1, num);
}

template <typename T, class A>
void CUtlVector<T, A>::SetCount(int count) {
	RemoveAll();
	AddMultipleToTail(count);
}

template <typename T, class A>
inline void CUtlVector<T, A>::SetSize(int size) {
	SetCount(size);
}

template <typename T, class A>
void CUtlVector<T, A>::CopyArray(const T* pArray, int size) {
	Assert((Base() == NULL) || !pArray || (Base() >= (pArray + size)) || (pArray >= (Base() + Count())));

	SetSize(size);
	for (int i = 0; i < size; i++) {
		(*this)[i] = pArray[i];
	}
}

// template <typename T, class A>
// void CUtlVector<T, A>::Swap(CUtlVector<T, A>& vec) {
	// m_Memory.Swap(vec.m_Memory);
	// std::swap(m_Size, vec.m_Size);
	// swap(m_pElements, vec.m_pElements);
// }

template <typename T, class A>
int CUtlVector<T, A>::AddVectorToTail(CUtlVector const& src) {
	Assert(&src != this);

	int base = Count();

	AddMultipleToTail(src.Count());

	for (int i = 0; i < src.Count(); i++) {
		(*this)[base + i] = src[i];
	}

	return base;
}

template <typename T, class A>
inline int CUtlVector<T, A>::InsertMultipleBefore(int elem, int num, const T* pToInsert) {
	if (num == 0)
		return elem;

	Assert((elem == Count()) || IsValidIndex(elem));

	GrowVector(num);
	ShiftElementsRight(elem, num);

	for (int i = 0; i < num; ++i)
		Construct(&Element(elem + i));

	if (pToInsert) {
		for (int i = 0; i < num; i++) {
			Element(elem + i) = pToInsert[i];
		}
	}

	return elem;
}

template <typename T, class A>
int CUtlVector<T, A>::Find(const T& src) const {
	for (int i = 0; i < Count(); ++i) {
		if (Element(i) == src)
			return i;
	}
	return -1;
}

template <typename T, class A>
bool CUtlVector<T, A>::HasElement(const T& src) const {
	return (Find(src) >= 0);
}

template <typename T, class A>
void CUtlVector<T, A>::FastRemove(int elem) {
	Assert(IsValidIndex(elem));

	Destruct(&Element(elem));
	if (m_Size > 0) {
		memcpy(&Element(elem), &Element(m_Size - 1), sizeof(T));
		--m_Size;
	}
}

template <typename T, class A>
void CUtlVector<T, A>::Remove(int elem) {
	Destruct(&Element(elem));
	ShiftElementsLeft(elem);
	--m_Size;
}

template <typename T, class A>
bool CUtlVector<T, A>::FindAndRemove(const T& src) {
	int elem = Find(src);
	if (elem != -1) {
		Remove(elem);
		return true;
	}
	return false;
}

template <typename T, class A>
void CUtlVector<T, A>::RemoveMultiple(int elem, int num) {
	Assert(elem >= 0);
	Assert(elem + num <= Count());

	for (int i = elem + num; --i >= elem;)
		Destruct(&Element(i));

	ShiftElementsLeft(elem, num);
	m_Size -= num;
}

template <typename T, class A>
void CUtlVector<T, A>::RemoveAll() {
	for ( int i = m_Size; --i >= 0; ) {
//		Destruct( &Element(i) );
	}

	m_Size = 0;
}

template <typename T, class A>
inline void CUtlVector<T, A>::Purge() {
	RemoveAll();
	m_Memory.Purge();
	ResetDbgInfo();
}

template <typename T, class A>
inline void CUtlVector<T, A>::PurgeAndDeleteElements() {
	for (int i = 0; i < m_Size; i++) {
		delete Element(i);
	}
	Purge();
}

template <typename T, class A>
inline void CUtlVector<T, A>::Compact() {
	m_Memory.Purge(m_Size);
}

template <typename T, class A>
inline int CUtlVector<T, A>::NumAllocated() const {
	return m_Memory.NumAllocated();
}

template <class T, class I>
CUtlMemory<T, I>::CUtlMemory(int nGrowSize, int nInitAllocationCount)
		: m_pMemory(0)
		, m_nAllocationCount(nInitAllocationCount)
		, m_nGrowSize(nGrowSize)
{
	ValidateGrowSize();
	Assert(nGrowSize >= 0);
	if (m_nAllocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}

template <class T, class I>
CUtlMemory<T, I>::CUtlMemory(T* pMemory, int numElements)
		: m_pMemory(pMemory)
		, m_nAllocationCount(numElements)
{
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template <class T, class I>
CUtlMemory<T, I>::CUtlMemory(const T* pMemory, int numElements)
		: m_pMemory((T*)pMemory)
		, m_nAllocationCount(numElements)
{
	m_nGrowSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template <class T, class I>
CUtlMemory<T, I>::~CUtlMemory() {
	Purge();
}

template <class T, class I>
void CUtlMemory<T, I>::Init(int nGrowSize /*= 0*/, int nInitSize /*= 0*/) {
	Purge();

	m_nGrowSize = nGrowSize;
	m_nAllocationCount = nInitSize;
	ValidateGrowSize();
	Assert(nGrowSize >= 0);
	if (m_nAllocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}

// template <class T, class I>
// void CUtlMemory<T, I>::Swap(CUtlMemory<T, I>& mem) {
	// swap(m_nGrowSize, mem.m_nGrowSize);
	// swap(m_pMemory, mem.m_pMemory);
	// swap(m_nAllocationCount, mem.m_nAllocationCount);
// }

template <class T, class I>
void CUtlMemory<T, I>::ConvertToGrowableMemory(int nGrowSize) {
	if (!IsExternallyAllocated())
		return;

	m_nGrowSize = nGrowSize;
	if (m_nAllocationCount) {
		UTLMEMORY_TRACK_ALLOC();
		MEM_ALLOC_CREDIT_CLASS();

		int nNumBytes = m_nAllocationCount * sizeof(T);
		T* pMemory = (T*)malloc(nNumBytes);
		memcpy(pMemory, m_pMemory, nNumBytes);
		m_pMemory = pMemory;
	} else {
		m_pMemory = NULL;
	}
}

template <class T, class I>
void CUtlMemory<T, I>::SetExternalBuffer(T* pMemory, int numElements) {
	Purge();

	m_pMemory = pMemory;
	m_nAllocationCount = numElements;

	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template <class T, class I>
void CUtlMemory<T, I>::SetExternalBuffer(const T* pMemory, int numElements) {
	Purge();

	m_pMemory = const_cast<T*>(pMemory);
	m_nAllocationCount = numElements;

	m_nGrowSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template <class T, class I>
void CUtlMemory<T, I>::AssumeMemory(T* pMemory, int numElements) {
	Purge();

	m_pMemory = pMemory;
	m_nAllocationCount = numElements;
}

template <class T, class I>
inline T& CUtlMemory<T, I>::operator[](I i) {
	Assert(!IsReadOnly());
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template <class T, class I>
inline const T& CUtlMemory<T, I>::operator[](I i) const {
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template <class T, class I>
inline T& CUtlMemory<T, I>::Element(I i) {
	Assert(!IsReadOnly());
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template <class T, class I>
inline const T& CUtlMemory<T, I>::Element(I i) const {
	Assert(IsIdxValid(i));
	return m_pMemory[i];
}

template <class T, class I>
bool CUtlMemory<T, I>::IsExternallyAllocated() const {
	return (m_nGrowSize < 0);
}

template <class T, class I>
bool CUtlMemory<T, I>::IsReadOnly() const {
	return (m_nGrowSize == EXTERNAL_CONST_BUFFER_MARKER);
}

template <class T, class I>
void CUtlMemory<T, I>::SetGrowSize(int nSize) {
	Assert(!IsExternallyAllocated());
	Assert(nSize >= 0);
	m_nGrowSize = nSize;
	ValidateGrowSize();
}

template <class T, class I>
inline T* CUtlMemory<T, I>::Base() {
	Assert(!IsReadOnly());
	return m_pMemory;
}

template <class T, class I>
inline const T* CUtlMemory<T, I>::Base() const {
	return m_pMemory;
}

template <class T, class I>
inline int CUtlMemory<T, I>::NumAllocated() const {
	return m_nAllocationCount;
}

template <class T, class I>
inline int CUtlMemory<T, I>::Count() const {
	return m_nAllocationCount;
}

template <class T, class I>
inline bool CUtlMemory<T, I>::IsIdxValid(I i) const {
	return (((int)i) >= 0) && (((int)i) < m_nAllocationCount);
}

inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem) {
	if (nGrowSize) {
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	} else {
		if (!nAllocationCount) {
			nAllocationCount = (31 + nBytesItem) / nBytesItem;
		}

		while (nAllocationCount < nNewSize) {
			nAllocationCount *= 2;
		}
	}

	return nAllocationCount;
}

template <class T, class I>
void CUtlMemory<T, I>::Grow(int num) {
	Assert(num > 0);

	if (IsExternallyAllocated()) {
		Assert(0);
		return;
	}

	int nAllocationRequested = m_nAllocationCount + num;

	UTLMEMORY_TRACK_FREE();

	m_nAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

	if ((int)(I)m_nAllocationCount < nAllocationRequested) {
		if ((int)(I)m_nAllocationCount == 0 && (int)(I)(m_nAllocationCount - 1) >= nAllocationRequested) {
			--m_nAllocationCount;
		} else {
			if ((int)(I)nAllocationRequested != nAllocationRequested) {
				Assert(0);
				return;
			}
			while ((int)(I)m_nAllocationCount < nAllocationRequested) {
				m_nAllocationCount = (m_nAllocationCount + nAllocationRequested) / 2;
			}
		}
	}

	UTLMEMORY_TRACK_ALLOC();

	if (m_pMemory) {
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
		Assert(m_pMemory);
	} else {
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
		Assert(m_pMemory);
	}
}

template <class T, class I>
inline void CUtlMemory<T, I>::EnsureCapacity(int num) {
	if (m_nAllocationCount >= num)
		return;

	if (IsExternallyAllocated()) {
		Assert(0);
		return;
	}

	UTLMEMORY_TRACK_FREE();

	m_nAllocationCount = num;

	UTLMEMORY_TRACK_ALLOC();

	if (m_pMemory) {
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
	} else {
		MEM_ALLOC_CREDIT_CLASS();
		m_pMemory = (T*)malloc(m_nAllocationCount * sizeof(T));
	}
}

template <class T, class I>
void CUtlMemory<T, I>::Purge() {
	if (!IsExternallyAllocated()) {
		if (m_pMemory) {
			UTLMEMORY_TRACK_FREE();
			free((void*)m_pMemory);
			m_pMemory = 0;
		}
		m_nAllocationCount = 0;
	}
}

template <class T, class I>
void CUtlMemory<T, I>::Purge(int numElements) {
	Assert(numElements >= 0);

	if (numElements > m_nAllocationCount) {
		Assert(numElements <= m_nAllocationCount);
		return;
	}

	if (numElements == 0) {
		Purge();
		return;
	}

	if (IsExternallyAllocated()) {
		return;
	}

	if (numElements == m_nAllocationCount) {
		return;
	}

	if (!m_pMemory) {
		Assert(m_pMemory);
		return;
	}

	UTLMEMORY_TRACK_FREE();

	m_nAllocationCount = numElements;

	UTLMEMORY_TRACK_ALLOC();

	MEM_ALLOC_CREDIT_CLASS();
	m_pMemory = (T*)realloc(m_pMemory, m_nAllocationCount * sizeof(T));
}