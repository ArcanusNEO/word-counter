# word-counter
计算英语文章词频的工具

#### Examples:

```shell
word-counter -i 'demo/Pride and Prejudice.txt' -o 'demo/Pride and Prejudice Word Count.json' -s 'Stop Words.txt'
```

其中，选项-i之后的参数指明输入文件，-o之后的参数指明输出文件，-s之后的参数指明停用词表。

另附赠了一份英文停用词表Stop Words.txt。:)

**注意：**程序将对停用词表实行全字匹配，但会将符号 ' 开头的词视为独立词，并全部小写化字母。也就是说，在停用词表里出现大写字母是没有意义的。

