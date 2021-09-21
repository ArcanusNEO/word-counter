# word-counter

统计英语文章词频，并以json格式输出的工具

另附赠了一份英文停用词表stop-words-eng.txt。:)

#### Examples:

```shell
word-counter -v
```

程序会从当前目录下查找停词表stop-words-eng.txt，默认从标准输入读取文章，并默认向标准输出打印json格式的词频信息。其中，-v选项表明使用verbose模式，会先输出一些统计信息。

```shell
word-counter -i 'demo/Pride and Prejudice.txt' -o 'demo/Pride and Prejudice Word Count.json' -s 'stop-words-eng.txt'
```

其中，选项-i之后的参数指明输入文件，- 或 – 表示使用标准输入，-o之后的参数指明输出文件，- 或 – 表示使用标准输出，-s之后的参数指明停用词表。

注意：程序将对停用词表实行全字匹配，但会将符号 ' 开头的词视为独立词，并全部小写化字母。也就是说，在停用词表里出现大写字母是没有意义的。
