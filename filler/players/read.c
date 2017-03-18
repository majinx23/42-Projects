/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 21:10:39 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/19 17:42:35 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
	assert(argc == 2);
	char* fn = argv[1];
	FILE* f = fopen(fn, "rb");
	printf("char a[] = {\n");
	unsigned long n = 0;
	while(!feof(f)) {
		unsigned char c;
		if(fread(&c, 1, 1, f) == 0) break;
		printf("%c", c);
		++n;
//		if (n % 10 == 0) printf("\n");
	}
	fclose(f);
	printf("};\n");
}
