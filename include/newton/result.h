#pragma once
#include <string>

namespace newton
{
    /// @brief A utility class for handling operation results and errors in a type-safe manner, without using exceptions.
    template <typename T>
    class Result
    {
    public:
        /// @brief Constructs a Result object directly, implicitly.
        /// @param value
        Result(T value) : value(std::move(value)), error_msg("") {}

        /// @brief Factory method for creating a successful Result object.
        /// @param value The value to be stored in the Result object.
        static Result<T> success(T value)
        {
            return Result<T>(value);
        }

        /// @brief Factory method for creating an error Result object.
        /// @param error_msg The error message to be stored in the Result object, explaining why the error.
        static Result<T> error(std::string error_msg)
        {
            return Result<T>(error_msg);
        }

        /// @brief Checks if the Result object has an error.
        /// @return True if the Result object has an error, false otherwise.
        bool has_error() const
        {
            return !error_msg.empty();
        }

        /// @brief Gets the value stored in the Result object.
        /// @note The value may be invalid if the Result object has an error.
        /// @see has_error()
        /// @see get_value_or()
        /// @return The value stored in the Result object.
        T get_value() const
        {
            return value;
        }

        /// @brief Gets the error message stored in the Result object.
        /// @return The error message stored in the Result object, empty if there is no error.
        std::string get_error_msg() const
        {
            return error_msg;
        }

        /// @brief Safe way to get the value stored in the Result object.
        /// @param default_value The value to be returned if the Result object has an error.
        /// @return The value stored in the Result object if there is no error, otherwise the default value.
        T get_value_or(T default_value) const
        {
            return has_error() ? default_value : value;
        }

    private:
        Result() = delete;
        Result(T value, std::string error_msg)
            : value(std::move(value)), error_msg(std::move(error_msg))
        {
        }

        Result(std::string error_msg) : error_msg(std::move(error_msg)) {}

        T value;
        std::string error_msg;
    };

    /// @brief A utility class for handling operation results and errors in a type-safe manner, without using exceptions.
    /// @details Specialization for functions that do not return a value (void).
    template <>
    class Result<void>
    {
    public:
        /// @brief Constructs a Result object directly, implicitly.
        static Result<void> success();

        /// @brief Factory method for creating an error Result object.
        /// @param error_msg The error message to be stored in the Result object, explaining why the error.
        static Result<void> error(std::string error_msg);

        /// @brief Checks if the Result object has an error.
        /// @return True if the Result object has an error, false otherwise.
        bool has_error() const
        {
            return !error_msg.empty();
        };

        /// @brief Gets the error message stored in the Result object.
        /// @return The error message stored in the Result object, empty if there is no error.
        std::string get_error_msg() const
        {
            return error_msg;
        }

    private:
        explicit Result(std::string error_msg) : error_msg(std::move(error_msg)) {}

        std::string error_msg;
    };
} // namespace newton