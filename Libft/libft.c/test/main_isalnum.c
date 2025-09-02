int main(void)
{
    printf("ft_isalnum('a') = %d\n", ft_isalnum('a')); // 1
    printf("ft_isalnum('Z') = %d\n", ft_isalnum('Z')); // 1
    printf("ft_isalnum('5') = %d\n", ft_isalnum('5')); // 1
    printf("ft_isalnum('*') = %d\n", ft_isalnum('*')); // 0
    printf("ft_isalnum(' ') = %d\n", ft_isalnum(' ')); // 0
    return 0;
}