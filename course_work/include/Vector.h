#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector
{
private:
	T* data_;
	size_t size_;
	size_t capacity_;
public:

	Vector() : data_(nullptr), size_(0), capacity_(0) {}

	Vector(size_t n) : data_(n ? new T[n]{} : nullptr), size_(n), capacity_(n) {}

	Vector(size_t n, const T& value) : Vector(n)
	{
		for (size_t i = 0; i < n; i++) {
			data_[i] = value;
		}
	}

	Vector(const Vector& other) : data_(other.capacity_ ? new T[other.capacity_] : nullptr), size_(other.size_), capacity_(other.capacity_)
	{
		for (size_t i = 0; i < other.size_; i++) {
			data_[i] = other.data_[i];
		}
	}

	Vector(Vector&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) 
	{
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}
	~Vector() { delete[] data_; }

	Vector& operator=(const Vector& other)
	{
		if (this == &other) return *this;

		T* newData = new T[other.capacity_];
		for (size_t i = 0; i < other.size_; i++) {
			newData[i] = other.data_[i];
		}
		delete[] data_;
		data_ = newData;
		size_ = other.size_;
		capacity_ = other.capacity_;
		return *this;
	}

	Vector& operator=(Vector&& other)
	{
		if (this == &other) return *this;
		delete[] data_;

		data_ = other.data_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
		return *this;
	}

	bool operator==(const Vector& other) const
	{
		if (size_ == other.size_) {
			for (size_t i = 0; i < size_; i++) {
				if (data_[i] != other.data_[i]) return false;
			}
			return true;
		}
		return false;
	}

	bool operator!=(const Vector& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Vector& other) const
	{
		size_t minSize = (size_ < other.size_) ? size_ : other.size_;
		for (size_t i = 0; i < minSize; i++) {
			if (data_[i] < other.data_[i]) return true;
			if (data_[i] > other.data_[i]) return false;
		}
		return size_ < other.size_;
	}

	bool operator>(const Vector& other) const
	{
		return other < *this;
	}

	bool operator<=(const Vector& other) const
	{
		return !(*this > other);
	}

	bool operator>=(const Vector& other) const
	{
		return !(*this < other);
	}

	T& operator[](size_t index)
	{
		return data_[index];
	}

	const T& operator[](size_t index) const
	{
		return data_[index];
	}

	T& at(size_t index)
	{
		if (index >= size_) throw std::out_of_range("Argument is out of range");
		return data_[index];
	}

	const T& at(size_t index) const
	{
		if (index >= size_) throw std::out_of_range("Argument is out of range");
		return data_[index];
	}

	T& front()
	{
		if (!size_) throw std::out_of_range("Vector is empty");
		return data_[0];
	}
	
	const T& front() const
	{
		if (!size_) throw std::out_of_range("Vector is empty");
		return data_[0];
	}

	T& back()
	{
		if (!size_) throw std::out_of_range("Vector is empty");
		return data_[size_ - 1];
	}

	const T& back() const
	{
		if (!size_) throw std::out_of_range("Vector is empty");
		return data_[size_ - 1];
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	void push_back(const T& value)
	{
		if (size_ == capacity_) {
			size_t newCapacity = !capacity_ ? 1 : capacity_ * 2;
			T* newData = new T[newCapacity];
			for (size_t i = 0; i < size_; i++) {
				newData[i] = data_[i];
			}
			delete[] data_;
			data_ = newData;
			capacity_ = newCapacity;
		}
		data_[size_] = value;
		size_++;
	}

	void push_back(T&& value)
	{
		if (size_ == capacity_) {
			size_t newCapacity = !capacity_ ? 1 : capacity_ * 2;
			T* newData = new T[newCapacity];
			for (size_t i = 0; i < size_; i++) {
				newData[i] = data_[i];
			}
			delete[] data_;
			data_ = newData;
			capacity_ = newCapacity;
		}
		data_[size_] = std::move(value);
		size_++;
	}

	void insert(size_t index, const T& value)
	{
		if (index > size_) throw std::out_of_range("Index is out of range");

		if (size_ == capacity_) {
			size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
			T* newData = new T[newCapacity];

			for (size_t i = 0; i < index; i++) {
				newData[i] = std::move(data_[i]);
			}

			newData[index] = value;

			for (size_t i = index; i < size_; i++) {
				newData[i + 1] = std::move(data_[i]);
			}

			delete[] data_;
			data_ = newData;
			capacity_ = newCapacity;
		}
		else {
			for (size_t i = size_; i > index; i--) {
				data_[i] = std::move(data_[i - 1]);
			}
			data_[index] = value;
		}

		size_++;
	}

	void pop_back()
	{
		if (!size_) throw std::out_of_range("Vector is empty");
		size_--;
	}

	void erase(size_t index)
	{
		if (index >= size_) throw std::out_of_range("Index is out of range");

		for (size_t i = index; i + 1 < size_; i++) {
			data_[i] = std::move(data_[i + 1]);
		}

		size_--;
	}

	void erase(size_t first, size_t last)
	{
		if (first > last || last > size_) {
			throw std::out_of_range("Index is out of range");
		}

		size_t count = last - first;
		for (size_t i = first; i + count < size_; i++) {
			data_[i] = std::move(data_[i + count]);
		}

		size_ -= count;
	}

	void clear() {
		size_ = 0;
	}

	void resize(size_t new_size)
	{
		if (new_size < size_) {
			size_ = new_size;
		}

		if (new_size > size_) {
			if (new_size >= capacity_) {
				size_t newCapacity = (capacity_ == 0 ? 1 : capacity_ * 2);
				if (new_size > newCapacity) { newCapacity = new_size; }
				T* newData = new T[newCapacity];

				for (size_t i = 0; i < size_; i++) {
					newData[i] = std::move(data_[i]);
				}

				for (size_t i = size_; i < new_size; i++) {
					newData[i] = {};
				}

				delete[] data_;
				data_ = newData;
				capacity_ = newCapacity;
			}
			else {
				for (size_t i = size_; i < new_size; i++) {
					data_[i] = {};
				}
			}
			size_ = new_size;
		}
	}

	void resize(size_t new_size, const T& value)
	{
		if (new_size < size_) {
			size_ = new_size;
		}

		if (new_size > size_) {
			if (new_size >= capacity_) {
				size_t newCapacity = (capacity_ == 0 ? 1 : capacity_ * 2);
				if (new_size > newCapacity) { newCapacity = new_size; }
				T* newData = new T[newCapacity];

				for (size_t i = 0; i < size_; i++) {
					newData[i] = std::move(data_[i]);
				}

				for (size_t i = size_; i < new_size; i++) {
					newData[i] = value;
				}

				delete[] data_;
				data_ = newData;
				capacity_ = newCapacity;
			}
			else {
				for (size_t i = size_; i < new_size; i++) {
					data_[i] = value;
				}
			}
			size_ = new_size;
		}

	}

	void swap(Vector& other)
	{
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}



};
