下面记录了一些实现pyssh的细节
* AsRef<Path>可以接受`String`类型作为参数。String实现了`AsRef<str>`，而`str`实现了`AsRef<Path>`