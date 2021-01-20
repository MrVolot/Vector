#pragma once
#include<iostream>
namespace MyVector {
	template <typename T>
	class vector {//emplace_back()
		T* data_{ nullptr };
		size_t size_{};
		size_t capacity_{};
		void copy(const T* member, size_t size);
		void reAllocate(size_t cap);
	public:
		vector();
		vector(const T& rhs);
		vector(const std::initializer_list<T>& list);
		vector(const MyVector::vector<T>& rhs);
		vector(const MyVector::vector<T>&& rhs);
		~vector();
		void push_back(const T& element);
		void push_back(T&& element);
		template <typename ...Args>
		void emplace_back(Args&&... args);
		T operator[](size_t num);
		T* begin();
		T* end();
		size_t size();
		size_t capacity();
		void resize(size_t num);
		T& at(size_t number);
		void clear();
		void swap(vector& vec);
		void shrink_to_fit();
		void insert(int pos, const T& value);
	};
	template <typename T>
	vector<T>::vector() :size_{ 0 }, capacity_{ 1 } {
		data_ = static_cast<T*>(malloc(sizeof(T)*capacity_)) ;
	}

	template <typename T>
	vector<T>::vector(const T& rhs) : data_{ static_cast<T*>(malloc(sizeof (T))) }, size_{ 1 }, capacity_{ 1 } {
		//placement new
		new(&data_[0])T{ rhs };
	}
	template <typename T>
	vector<T>::vector(const vector& rhs) : size_{ rhs.size_ }, capacity_{ rhs.capacity_ } {
		copy(rhs.data_, rhs.capacity_);
	}//malloc
	template <typename T>
	vector<T>::vector(const std::initializer_list<T>& list) : data_{ static_cast<T*>(malloc(sizeof(T)*list.size()) )}, size_{ list.size() }, capacity_{ list.size() } {
		size_t j{};
		for (auto i{ list.begin() }; i != list.end(); ++i, ++j) {
			new(&data_[j])T{ *i };
		}

	}
	template <typename T>
	vector<T>::vector(const vector&& rhs) : data_{rhs.data_} ,size_ { rhs.size_ }, capacity_{ rhs.capacity_ }{
		rhs.data_ = nullptr;
		rhs.size_ = 0;
		rhs.capacity_ = 0;
	}
	template <typename T>
	vector<T>::~vector(){
		if (data_ != nullptr) {
			for (size_t i = 0; i < size_; i++) {
				data_[i].~T();
			}
			free(data_);
	    }
	}
	template <typename T>
	void vector<T>::copy(const T* member, size_t size) {
		data_ =static_cast<T*> (malloc(sizeof(T)*size));
		for (int i{}; i < size; ++i) {
			new(&data_[i])T{ member[i] };
		}
	}

	template <typename T>
	void vector<T>::reAllocate(size_t cap) {
		capacity_ = cap;// 1 2 3 
		T* buffer{ static_cast<T*>(malloc(sizeof(T)*cap)) };
		for (int i{}; i < size_; i++) {
			new(&buffer[i])T{ data_[i] };
		}
		for (size_t i = 0; i < size_; i++) {
			data_[i].~T();
		}
		free(data_);
		data_ = buffer;
	}

	template <typename T>
	void vector<T>::push_back(const T& element){
		if (capacity_ == size_) {
			reAllocate(capacity_ * 2);
		}
		new(&data_[size_++])T{ element };
	}

	template <typename T>
	template <typename ...Args>
	void vector<T>::emplace_back(Args&&... args) {
		if (capacity_ == size_) {
			reAllocate(capacity_ * 2);
		}
		new(&data_[size_++])T{ std::forward<Args>(args)... };
	}
	template <typename T>
	T vector<T>::operator[](size_t num) {
		return data_[num];
	}

	template <typename T>
	T* vector<T>::begin() {
		return data_;
	}


	template <typename T>
	T* vector<T>::end() {
		return data_ + size_;
	}


	template <typename T>
	size_t vector<T>::size() {
		return size_;
	}

	template <typename T>
	size_t vector<T>::capacity() {
		return capacity_;
	}
	template <typename T>
	void vector<T>::push_back(T&& element) {
		if (capacity_ == size_) {
			reAllocate(capacity_ * 2);
		}
		new(&data_[size_++])T{ std::move(element) };
	}
	template <typename T>
	void vector<T>::resize(size_t num) {
		if (num < size_) {
			for (size_t i = (size_ - num); i < size_; i++) {
				data_[i].~T();
			}
			size_ = num;
			return;
		}
		if (num + size_ > capacity_)
			reAllocate(num + size_);
		for (size_t i = size_; i < num; i++) {
			new(&data_[i])T{};
		}
		size_ = num;
	}
	template <typename T>
	T& vector<T>::at(size_t number) {
		return data_[number];
	}
	template <typename T>
	void vector<T>::clear() {
		for (size_t i = 0; i < size_; i++) {
			data_[i].~T();
		}
		size_ = 0;
	}
	template <typename T>
	void vector<T>::swap(vector& vec) {
		auto tmp{vec};
		vec.resize(size_);
		vec.clear();
		for (size_t i{ 0 }; i < size_; i++) {
			vec.push_back(data_[i]);
		}
		resize(tmp.size());
		clear();
		for (size_t i{ 0 }; i < tmp.size_; i++) {
			push_back(tmp[i]);
		}
	}
	template <typename T>
<<<<<<< HEAD
	void vector<T>::shrink_to_fit() {
		capacity_ = size_;
		T* temp=static_cast<T*>(malloc(size_*sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			temp[i] = data_[i];
		}
		for (size_t i = 0; i < size_; i++) {
			data_[i].~T();
		}
		free(data_);
		data_ = temp;
	}
=======
	void vector<T>::insert(int pos, const T& value) {
		if (capacity_ == size_) {
			reAllocate(capacity_ * 2);
		}
		size_++;
		for (int i = size_-1; i > pos; i--) {
			data_[i]=data_[i-1];
		}
		data_[pos] = value;
	}
	
>>>>>>> insert
}
