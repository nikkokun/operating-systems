#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>

int main() {
		int mib[2];
		unsigned int freq;
		size_t len;

		mib[0] = CTL_HW;
		mib[1] = HW_CPU_FREQ;
		len = sizeof(freq);
		sysctl(mib, 2, &freq, &len, NULL, 0);

		printf("%u\n", freq);

		return 0;
}