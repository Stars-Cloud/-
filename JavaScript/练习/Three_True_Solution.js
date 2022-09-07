console.log([] == 0);
console.log(![] == 0);
console.log([] == ![]);

/*  当进行双等号比较时候： 先检查两个操作数数据类型，
	如果相同， 则进行===比较， 如果不同， 则愿意为你进行一次类型转换， 
	转换成相同类型后再进行比较， 而===比较时， 如果类型不同，直接就是false. 
	
	相同的字符串、数值上相等的数字、相同的对象、相同的 Boolean 值或者（当类型不同时）
	能被强制转化为上述情况之一，均被认为是相等的。
*/

/* 	
	[] == 0
	第一个：Array == Number 
		左边转换 Number([]) = 0 故为true
		右边转换 Array(0) = [] 故为true
	
	![] == 0	
	第二个：Boolean == Number
		左边转换 Number(![]) = 0 故为true
		右边转换 Boolean(0) = false 故为true
		
	[] == ![]	
	第三个：Array == Boolean
		
 */