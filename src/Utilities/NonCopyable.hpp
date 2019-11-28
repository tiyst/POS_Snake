//
// Created by tiyst on 22/11/2019.
//

#ifndef SNAKERINO_NONCOPYABLE_HPP
#define SNAKERINO_NONCOPYABLE_HPP


struct NonCopyable {
//	NonCopyable() = default;
//	NonCopyable& operator = (const NonCopyable&) = delete;
//	NonCopyable(const NonCopyable&) = delete;


	NonCopyable() = default;
	NonCopyable& operator = (const NonCopyable&) = delete;
	NonCopyable(const NonCopyable&) = delete;
};


#endif //SNAKERINO_NONCOPYABLE_HPP
