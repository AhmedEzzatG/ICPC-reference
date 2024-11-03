static class MScanner {
	StringTokenizer st;
	BufferedReader br;
	public MScanner(InputStream system) {
		br = new BufferedReader(new InputStreamReader(system));
	}

	public MScanner(String file) throws Exception {
		br = new BufferedReader(new FileReader(file));
	}

	public String next() throws IOException {
		while (st == null  !st.hasMoreTokens())
			st = new StringTokenizer(br.readLine());
		return st.nextToken();
	}
	public String nextLine() throws IOException {
		return br.readLine();
	}

	public int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}

	public char nextChar() throws IOException {
		return next().charAt(0);
	}

	public long nextLong() throws IOException {
		return Long.parseLong(next());
	}

	public int[] intArr(int n) throws IOException {
		int[]in=new int[n];for(int i=0;in;i++)in[i]=nextInt();
		return in;
	}
	public long[] longArr(int n) throws IOException {
		long[]in=new long[n];for(int i=0;in;i++)in[i]=nextLong();
		return in;
	}
	public int[] intSortedArr(int n) throws IOException {
		int[]in=new int[n];for(int i=0;in;i++)in[i]=nextInt();
		shuffle(in);
		Arrays.sort(in);
		return in;
	}
	public long[] longSortedArr(int n) throws IOException {
		long[]in=new long[n];for(int i=0;in;i++)in[i]=nextLong();
		shuffle(in);
		Arrays.sort(in);
		return in;
	}
	static void shuffle(int[]in) {
		for(int i=0;iin.length;i++) {
			int idx=(int)(Math.random()in.length);
			int tmp=in[i];
			in[i]=in[idx];
			in[idx]=tmp;
		}
	}
	static void shuffle(long[]in) {
		for(int i=0;iin.length;i++) {
			int idx=(int)(Math.random()in.length);
			long tmp=in[i];
			in[i]=in[idx];
			in[idx]=tmp;
		}
	}
	public Integer[] IntegerArr(int n) throws IOException {
		Integer[]in=new Integer[n];for(int i=0;in;i++)in[i]=nextInt();
		return in;
	}
	public Long[] LongArr(int n) throws IOException {
		Long[]in=new Long[n];for(int i=0;in;i++)in[i]=nextLong();
		return in;
	}

	public boolean ready() throws IOException {
		return br.ready();
	}

	public void waitForInput() throws InterruptedException {
		Thread.sleep(3000);
	}
}