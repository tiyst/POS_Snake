//
// Created by tiyst on 23/11/2019.
//

#ifndef SNAKERINO_NONMOVABLE_HPP
#define SNAKERINO_NONMOVABLE_HPP

struct NonMovable
{
	NonMovable() = default;
	NonMovable& operator = (NonCopyable&&) = delete;
	NonMovable(NonCopyable&&) = delete;
};

#endif //SNAKERINO_NONMOVABLE_HPP
