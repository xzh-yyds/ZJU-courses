---------------Readme---------------

Work already done：
	基本要求:
		支持C++算数类型, std::string, 以及STL容器的二进制/xml(反)序列化
		可以方便地支持自定义类型的(反)序列化
		每个模块有自己的命名空间
	bonus1:
		使用base64的xml(反)序列化二进制模式
	bonus2：
		对智能指针的xml(反)序列化


Files:
	serialize_bin:
		二进制序列化模块及测试
		binSerialization.hpp	实现
		test_bin.cpp			测试样例

	serialize_xml:
		xml序列化模块及测试
		xmlSerialization.hpp	实现
		test_xml.cpp			测试样例

	test_bins:
		二进制序列化测试结果

	test_xmls:
		xml序列化测试结果
		
	test_xml_bin:
		基于base64的xml序列化二进制模式测试结果
	
	test_bin.exe: 二进制序列化测试的可执行文件
	
	test_xml.exe: xml序列化测试的可执行文件
	
	makefile: makefile


How to use:
	当前目录下打开终端或命令行；
	编译：
		g++ serialize_xml/*.cpp -o test_xml (xml序列化测试样例)
		g++ serialize_bin/*.cpp -o test_bin (二进制序列化测试样例)
	运行:
		./test_xml	(xml序列化测试样例)
		./test_bin	(二进制序列化测试样例)
	
	或者, 在支持makefile的情况下：
		make build_xml	(编译xml序列化测试样例)
		make build_bin	(编译二进制序列化测试样例)
		make run_xml	(运行xml序列化测试样例)
		make run_bin	(运行二进制序列化测试样例)
	