// Copyright (C) 2018-2026, Tellusim Technologies Inc. All rights reserved
// https://tellusim.com/

#include <core/TellusimLog.h>
#include <math/TellusimPolynomial.h>

/*
 */
using namespace Tellusim;

/*
 */
int32_t main(int32_t argc, char **argv) {
	
	using Tellusim::abs;
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		if(1) {
			
			float32_t ret[16];
			uint32_t counter = 0;
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 100.0f;
			for(float32_t c = -range; c < range; c += 0.99f) {
				for(float32_t b = -range; b < range; b += 0.99f) {
					for(float32_t a = -range; a < range; a += 0.99f) {
						uint32_t num = Polynomial::quadratic(a, b, c, ret);
						for(uint32_t i = 0; i < num; i++) {
							float32_t x = ret[i];
							float32_t y = x * (x * a + b) + c;
							if(abs(y) > 1e0f) TS_LOGF(Error, "quadratic32: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c);
							worse = max(worse, abs(y));
							error += abs(y);
							counter += num;
						}
					}
				}
			}
			TS_LOGF(Message, "quadratic32: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float64_t ret[16];
			uint32_t counter = 0;
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 100.0;
			for(float64_t c = -range; c < range; c += 0.99) {
				for(float64_t b = -range; b < range; b += 0.99) {
					for(float64_t a = -range; a < range; a += 0.99) {
						uint32_t num = Polynomial::quadratic(a, b, c, ret);
						for(uint32_t i = 0; i < num; i++) {
							float64_t x = ret[i];
							float64_t y = x * (x * a + b) + c;
							if(abs(y) > 1e-8) TS_LOGF(Error, "quadratic64: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c);
							worse = max(worse, abs(y));
							error += abs(y);
							counter += num;
						}
					}
				}
			}
			TS_LOGF(Message, "quadratic64: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float32_t ret[16];
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 1000.0f;
			for(float32_t x0 = -range; x0 < range; x0 += 9.9f) {
				if(abs(x0) < 1e-6f) continue;
				for(float32_t x1 = -range; x1 < range; x1 += 0.9f) {
					if(abs(x1) < 1e-6f || x1 < x0 + 1.0f) continue;
					float32_t b = x0 + x1;
					float32_t c = x0 * x1;
					uint32_t num = Polynomial::quadratic(1.0f, -b, c, ret);
					if(num == 2) {
						worse = max(worse, abs(x0 - ret[0]));
						worse = max(worse, abs(x1 - ret[1]));
						error += abs(x0 - ret[0]);
						error += abs(x1 - ret[1]);
					} else {
						TS_LOGF(Fatal, "quadratic32: %f %f : %f %f %f : %u\n", x0, x1, 1.0, -b, c, num);
					}
				}
			}
			TS_LOGF(Message, "quadratic32: %16.9f / %-16.9f\n", error, worse);
		}
		
		if(1) {
			
			float64_t ret[16];
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 10000.0;
			for(float64_t x0 = -range; x0 < range; x0 += 9.9) {
				if(abs(x0) < 1e-6) continue;
				for(float64_t x1 = -range; x1 < range; x1 += 0.9) {
					if(abs(x1) < 1e-6 || x1 < x0 + 1.0) continue;
					float64_t b = x0 + x1;
					float64_t c = x0 * x1;
					uint32_t num = Polynomial::quadratic(1.0, -b, c, ret);
					if(num == 2) {
						worse = max(worse, abs(x0 - ret[0]));
						worse = max(worse, abs(x1 - ret[1]));
						error += abs(x0 - ret[0]);
						error += abs(x1 - ret[1]);
					} else {
						TS_LOGF(Fatal, "quadratic64: %f %f : %f %f %f : %u\n", x0, x1, 1.0, -b, c, num);
					}
				}
			}
			TS_LOGF(Message, "quadratic64: %16.9f / %-16.9f\n", error, worse);
		}
		
		// quadratic32:    538.510559082 / 0.107223190      / 20997664
		// quadratic64:      0.000001048 / 0.000000000      / 20997664
		// quadratic32:     23.912763596 / 0.017333984
		// quadratic64:      0.000094173 / 0.000000014
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		if(1) {
			
			float32_t ret[16];
			uint32_t counter = 0;
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 18.0f;
			for(float32_t d = -range; d < range; d += 0.99f) {
				for(float32_t c = -range; c < range; c += 0.99f) {
					for(float32_t b = -range; b < range; b += 0.99f) {
						for(float32_t a = -range; a < range; a += 0.33f) {
							uint32_t num = Polynomial::cubicFast(a, b, c, d, ret);
							for(uint32_t i = 0; i < num; i++) {
								float32_t x = ret[i];
								float32_t y = x * (x * (x * a + b) + c) + d;
								if(abs(y) > 1e-1f) TS_LOGF(Error, "cubic32f: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d);
								worse = max(worse, abs(y));
								error += abs(y);
								counter += num;
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   cubic32f: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float32_t ret[16];
			uint32_t counter = 0;
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 18.0f;
			for(float32_t d = -range; d < range; d += 0.99f) {
				for(float32_t c = -range; c < range; c += 0.99f) {
					for(float32_t b = -range; b < range; b += 0.99f) {
						for(float32_t a = -range; a < range; a += 0.33f) {
							uint32_t num = Polynomial::cubic(a, b, c, d, ret);
							for(uint32_t i = 0; i < num; i++) {
								float32_t x = ret[i];
								float32_t y = x * (x * (x * a + b) + c) + d;
								if(abs(y) > 1e-1f) TS_LOGF(Error, "cubic32: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d);
								worse = max(worse, abs(y));
								error += abs(y);
								counter += num;
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   cubic32:  %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float64_t ret[16];
			uint32_t counter = 0;
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 18.0;
			for(float64_t d = -range; d < range; d += 0.99) {
				for(float64_t c = -range; c < range; c += 0.99) {
					for(float64_t b = -range; b < range; b += 0.99) {
						for(float64_t a = -range; a < range; a += 0.33) {
							uint32_t num = Polynomial::cubicFast(a, b, c, d, ret);
							for(uint32_t i = 0; i < num; i++) {
								float64_t x = ret[i];
								float64_t y = x * (x * (x * a + b) + c) + d;
								if(abs(y) > 1e-5) TS_LOGF(Error, "cubic64f: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d);
								worse = max(worse, abs(y));
								error += abs(y);
								counter += num;
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   cubic64f: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float64_t ret[16];
			uint32_t counter = 0;
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 18.0;
			for(float64_t d = -range; d < range; d += 0.99) {
				for(float64_t c = -range; c < range; c += 0.99) {
					for(float64_t b = -range; b < range; b += 0.99) {
						for(float64_t a = -range; a < range; a += 0.33) {
							uint32_t num = Polynomial::cubic(a, b, c, d, ret);
							for(uint32_t i = 0; i < num; i++) {
								float64_t x = ret[i];
								float64_t y = x * (x * (x * a + b) + c) + d;
								if(abs(y) > 1e-5) TS_LOGF(Error, "cubic64: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d);
								worse = max(worse, abs(y));
								error += abs(y);
								counter += num;
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   cubic64:  %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float32_t ret[16];
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 50.0f;
			for(float32_t x0 = -range; x0 < range; x0 += 9.9f) {
				if(abs(x0) < 1e-6f) continue;
				for(float32_t x1 = -range; x1 < range; x1 += 0.9f) {
					if(abs(x1) < 1e-6f || x1 < x0 + 1.0f) continue;
					for(float32_t x2 = -range; x2 < range; x2 += 0.9f) {
						if(abs(x2) < 1e-6f || x2 < x1 + 1.0f) continue;
						float32_t b = x0 + x1 + x2;
						float32_t c = x0 * (x1 + x2) + x1 * x2;
						float32_t d = x0 * x1 * x2;
						uint32_t num = Polynomial::cubic(1.0f, -b, c, -d, ret);
						if(num == 3) {
							worse = max(worse, abs(x0 - ret[0]));
							worse = max(worse, abs(x1 - ret[1]));
							worse = max(worse, abs(x2 - ret[2]));
							error += abs(x0 - ret[0]);
							error += abs(x1 - ret[1]);
							error += abs(x2 - ret[2]);
						} else {
							TS_LOGF(Fatal, "cubic32: %f %f %f : %f %f %f %f : %u\n", x0, x1, x2, 1.0f, -b, c, -d, num);
						}
					}
				}
			}
			TS_LOGF(Message, "   cubic32:  %16.9f / %-16.9f\n", error, worse);
		}
		
		if(1) {
			
			float64_t ret[16];
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 1000.0;
			for(float64_t x0 = -range; x0 < range; x0 += 9.9) {
				if(abs(x0) < 1e-6) continue;
				for(float64_t x1 = -range; x1 < range; x1 += 9.9) {
					if(abs(x1) < 1e-6 || x1 < x0 + 1.0) continue;
					for(float64_t x2 = -range; x2 < range; x2 += 0.9) {
						if(abs(x2) < 1e-6 || x2 < x1 + 1.0) continue;
						float64_t b = x0 + x1 + x2;
						float64_t c = x0 * (x1 + x2) + x1 * x2;
						float64_t d = x0 * x1 * x2;
						uint32_t num = Polynomial::cubic(1.0, -b, c, -d, ret);
						if(num == 3) {
							worse = max(worse, abs(x0 - ret[0]));
							worse = max(worse, abs(x1 - ret[1]));
							worse = max(worse, abs(x2 - ret[2]));
							error += abs(x0 - ret[0]);
							error += abs(x1 - ret[1]);
							error += abs(x2 - ret[2]);
						} else {
							TS_LOGF(Fatal, "cubic64: %f %f %f : %f %f %f %f : %u\n", x0, x1, x2, 1.0, -b, c, -d, num);
						}
					}
				}
			}
			TS_LOGF(Message, "   cubic64:  %16.9f / %-16.9f\n", error, worse);
		}
		
		// cubic32f:    149.825332642 / 0.008453212      / 15336550
		// cubic32:     149.791183472 / 0.008395487      / 15336550
		// cubic64f:      0.000000655 / 0.000000000      / 15336558
		// cubic64:       0.000000512 / 0.000000000      / 15336558
		// cubic32:       0.674021840 / 0.009250641
		// cubic64:       0.000068778 / 0.000000024
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		if(1) {
			
			float32_t ret[16];
			uint32_t counter = 0;
			float32_t worse = 0.0;
			float32_t error = 0.0;
			float32_t range = 5.0;
			for(float32_t e = -range; e < range; e += 0.9f) {
				for(float32_t d = -range; d < range; d += 0.9f) {
					for(float32_t c = -range; c < range; c += 0.9f) {
						for(float32_t b = -range; b < range; b += 0.9f) {
							for(float32_t a = -range; a < range; a += 0.9f) {
								uint32_t num = Polynomial::quartic(a, b, c, d, e, ret);
								for(uint32_t i = 0; i < num; i++) {
									float32_t x = ret[i];
									float32_t y = x * (x * (x * (x * a + b) + c) + d) + e;
									if(abs(y) > 1e0f) TS_LOGF(Error, "quartic32: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d, e);
									worse = max(worse, abs(y));
									error += abs(y);
									counter += num;
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quartic32: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float64_t ret[16];
			uint32_t counter = 0;
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 5.0;
			for(float64_t e = -range; e < range; e += 0.9) {
				for(float64_t d = -range; d < range; d += 0.9) {
					for(float64_t c = -range; c < range; c += 0.9) {
						for(float64_t b = -range; b < range; b += 0.9) {
							for(float64_t a = -range; a < range; a += 0.9) {
								uint32_t num = Polynomial::quartic(a, b, c, d, e, ret);
								for(uint32_t i = 0; i < num; i++) {
									float64_t x = ret[i];
									float64_t y = x * (x * (x * (x * a + b) + c) + d) + e;
									if(abs(y) > 1e-8) TS_LOGF(Error, "quartic64: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d, e);
									worse = max(worse, abs(y));
									error += abs(y);
									counter += num;
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quartic64: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float32_t ret[16];
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 8.0f;
			for(float32_t x0 = -range; x0 < range; x0 += 0.9f) {
				if(abs(x0) < 1e-6f) continue;
				for(float32_t x1 = -range; x1 < range; x1 += 0.9f) {
					if(abs(x1) < 1e-6f || x1 < x0 + 1.0f) continue;
					for(float32_t x2 = -range; x2 < range; x2 += 0.9f) {
						if(abs(x2) < 1e-6f || x2 < x1 + 1.0f) continue;
						for(float32_t x3 = -range; x3 < range; x3 += 0.09f) {
							if(abs(x3) < 1e-6f || x3 < x2 + 1.0f) continue;
							float32_t b = x0 + x1 + x2 + x3;
							float32_t c = x0 * (x1 + x2 + x3) + x1 * (x2 + x3) + x2 * x3;
							float32_t d = x0 * (x1 * (x2 + x3) + x2 * x3) + x1 * x2 * x3;
							float32_t e = x0 * x1 * x2 * x3;
							uint32_t num = Polynomial::quartic(1.0f, -b, c, -d, e, ret);
							if(num == 4) {
								worse = max(worse, abs(x0 - ret[0]));
								worse = max(worse, abs(x1 - ret[1]));
								worse = max(worse, abs(x2 - ret[2]));
								worse = max(worse, abs(x3 - ret[3]));
								error += abs(x0 - ret[0]);
								error += abs(x1 - ret[1]);
								error += abs(x2 - ret[2]);
								error += abs(x3 - ret[3]);
							} else {
								TS_LOGF(Fatal, "quartic32: %f %f %f %f : %f %f %f %f %f : %u\n", x0, x1, x2, x3, 1.0f, -b, c, -d, e, num);
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quartic32: %16.9f / %-16.9f\n", error, worse);
		}
		
		if(1) {
			
			float64_t ret[16];
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 30.0;
			for(float64_t x0 = -range; x0 < range; x0 += 0.9) {
				if(abs(x0) < 1e-6) continue;
				for(float64_t x1 = -range; x1 < range; x1 += 0.9) {
					if(abs(x1) < 1e-6 || x1 < x0 + 1.0) continue;
					for(float64_t x2 = -range; x2 < range; x2 += 0.9) {
						if(abs(x2) < 1e-6 || x2 < x1 + 1.0) continue;
						for(float64_t x3 = -range; x3 < range; x3 += 0.09) {
							if(abs(x3) < 1e-6 || x3 < x2 + 1.0) continue;
							float64_t b = x0 + x1 + x2 + x3;
							float64_t c = x0 * (x1 + x2 + x3) + x1 * (x2 + x3) + x2 * x3;
							float64_t d = x0 * (x1 * (x2 + x3) + x2 * x3) + x1 * x2 * x3;
							float64_t e = x0 * x1 * x2 * x3;
							uint32_t num = Polynomial::quartic(1.0, -b, c, -d, e, ret);
							if(num == 4) {
								worse = max(worse, abs(x0 - ret[0]));
								worse = max(worse, abs(x1 - ret[1]));
								worse = max(worse, abs(x2 - ret[2]));
								worse = max(worse, abs(x3 - ret[3]));
								error += abs(x0 - ret[0]);
								error += abs(x1 - ret[1]);
								error += abs(x2 - ret[2]);
								error += abs(x3 - ret[3]);
							} else {
								TS_LOGF(Fatal, "quartic64: %f %f %f %f : %f %f %f %f %f : %u\n", x0, x1, x2, x3, 1.0, -b, c, -d, e, num);
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quartic64: %16.9f / %-16.9f\n", error, worse);
		}
		
		// quartic32:      4.053423405 / 0.014164972      / 846488
		// quartic64:      0.000000005 / 0.000000000      / 846492
		// quartic32:      0.037125356 / 0.000082493
		// quartic64:      0.000000627 / 0.000000000
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		if(1) {
			
			float32_t ret[16];
			uint32_t counter = 0;
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 5.0f;
			for(float32_t f = -range; f < range; f += 1.9f) {
				for(float32_t e = -range; e < range; e += 1.9f) {
					for(float32_t d = -range; d < range; d += 1.9f) {
						for(float32_t c = -range; c < range; c += 1.9f) {
							for(float32_t b = -range; b < range; b += 0.9f) {
								for(float32_t a = -range; a < range; a += 0.9f) {
									uint32_t num = Polynomial::quinticNr(a, b, c, d, e, f, ret, 1e3f);
									for(uint32_t i = 0; i < num; i++) {
										float32_t x = ret[i];
										float32_t y = x * (x * (x * (x * (x * a + b) + c) + d) + e) + f;
										if(abs(y) > 1e0f) TS_LOGF(Error, "quintic32: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d, e, f);
										worse = max(worse, abs(y));
										error += abs(y);
										counter += num;
									}
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quintic32: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float64_t ret[16];
			uint32_t counter = 0;
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 5.0;
			for(float64_t f = -range; f < range; f += 1.9) {
				for(float64_t e = -range; e < range; e += 1.9) {
					for(float64_t d = -range; d < range; d += 1.9) {
						for(float64_t c = -range; c < range; c += 1.9) {
							for(float64_t b = -range; b < range; b += 0.9) {
								for(float64_t a = -range; a < range; a += 0.9) {
									uint32_t num = Polynomial::quinticNr(a, b, c, d, e, f, ret, 1e3);
									for(uint32_t i = 0; i < num; i++) {
										float64_t x = ret[i];
										float64_t y = x * (x * (x * (x * (x * a + b) + c) + d) + e) + f;
										if(abs(y) > 1e-6) TS_LOGF(Error, "quintic64: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d, e, f);
										worse = max(worse, abs(y));
										error += abs(y);
										counter += num;
									}
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quintic64: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float32_t ret[16];
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 4.0f;
			for(float32_t x0 = -range; x0 < range; x0 += 0.9f) {
				if(abs(x0) < 1e-6f) continue;
				for(float32_t x1 = -range; x1 < range; x1 += 0.9f) {
					if(abs(x1) < 1e-6f || x1 < x0 + 1.0f) continue;
					for(float32_t x2 = -range; x2 < range; x2 += 0.9f) {
						if(abs(x2) < 1e-6f || x2 < x1 + 1.0f) continue;
						for(float32_t x3 = -range; x3 < range; x3 += 0.9f) {
							if(abs(x3) < 1e-6f || x3 < x2 + 1.0f) continue;
							for(float32_t x4 = -range; x4 < range; x4 += 0.09f) {
								if(abs(x4) < 1e-6f || x4 < x3 + 1.0f) continue;
								float32_t b = x0 + x1 + x2 + x3 + x4;
								float32_t c = x0 * (x1 + x2 + x3 + x4) + x1 * (x2 + x3 + x4) + x2 * (x3 + x4) + x3 * x4;
								float32_t d = x0 * (x1 * (x2 + x3 + x4) + x2 * (x3 + x4) + x3 * x4) + x1 * (x2 * (x3 + x4) + x3 * x4) + x2 * x3 * x4;
								float32_t e = x0 * (x1 * (x2 * (x3 + x4) + x3 * x4) + x2 * x3 * x4) + x1 * x2 * x3 * x4;
								float32_t f = x0 * x1 * x2 * x3 * x4;
								uint32_t num = Polynomial::quinticNr(1.0f, -b, c, -d, e, -f, ret, 1e3f);
								if(num == 5) {
									worse = max(worse, abs(x0 - ret[0]));
									worse = max(worse, abs(x1 - ret[1]));
									worse = max(worse, abs(x2 - ret[2]));
									worse = max(worse, abs(x3 - ret[3]));
									worse = max(worse, abs(x4 - ret[4]));
									error += abs(x0 - ret[0]);
									error += abs(x1 - ret[1]);
									error += abs(x2 - ret[2]);
									error += abs(x3 - ret[3]);
									error += abs(x4 - ret[4]);
								} else {
									TS_LOGF(Fatal, "quintic32: %f %f %f %f %f : %f %f %f %f %f %f : %u\n", x0, x1, x2, x3, x4, 1.0f, -b, c, -d, e, -f, num);
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quintic32: %16.9f / %-16.9f\n", error, worse);
		}
		
		if(1) {
			
			float64_t ret[16];
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 8.0;
			for(float64_t x0 = -range; x0 < range; x0 += 0.9) {
				if(abs(x0) < 1e-6) continue;
				for(float64_t x1 = -range; x1 < range; x1 += 0.9) {
					if(abs(x1) < 1e-6 || x1 < x0 + 1.0) continue;
					for(float64_t x2 = -range; x2 < range; x2 += 0.9) {
						if(abs(x2) < 1e-6 || x2 < x1 + 1.0) continue;
						for(float64_t x3 = -range; x3 < range; x3 += 0.9) {
							if(abs(x3) < 1e-6 || x3 < x2 + 1.0) continue;
							for(float64_t x4 = -range; x4 < range; x4 += 0.09) {
								if(abs(x4) < 1e-6 || x4 < x3 + 1.0) continue;
								float64_t b = x0 + x1 + x2 + x3 + x4;
								float64_t c = x0 * (x1 + x2 + x3 + x4) + x1 * (x2 + x3 + x4) + x2 * (x3 + x4) + x3 * x4;
								float64_t d = x0 * (x1 * (x2 + x3 + x4) + x2 * (x3 + x4) + x3 * x4) + x1 * (x2 * (x3 + x4) + x3 * x4) + x2 * x3 * x4;
								float64_t e = x0 * (x1 * (x2 * (x3 + x4) + x3 * x4) + x2 * x3 * x4) + x1 * x2 * x3 * x4;
								float64_t f = x0 * x1 * x2 * x3 * x4;
								uint32_t num = Polynomial::quinticNr(1.0, -b, c, -d, e, -f, ret, 1e3);
								if(num == 5) {
									worse = max(worse, abs(x0 - ret[0]));
									worse = max(worse, abs(x1 - ret[1]));
									worse = max(worse, abs(x2 - ret[2]));
									worse = max(worse, abs(x3 - ret[3]));
									worse = max(worse, abs(x4 - ret[4]));
									error += abs(x0 - ret[0]);
									error += abs(x1 - ret[1]);
									error += abs(x2 - ret[2]);
									error += abs(x3 - ret[3]);
									error += abs(x4 - ret[4]);
								} else {
									TS_LOGF(Fatal, "quintic64: %f %f %f %f %f : %f %f %f %f %f %f : %u\n", x0, x1, x2, x3, x4, 1.0, -b, c, -d, e, -f, num);
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "  quintic64: %16.9f / %-16.9f\n", error, worse);
		}
		
		// quintic32:     14.680234909 / 0.006802414      / 660909
		// quintic64:      0.000000027 / 0.000000000      / 657549
		// quintic32:      0.000028402 / 0.000000715
		// quintic64:      0.000000000 / 0.000000000
	}
	
	if(1) {
		
		TS_LOG(Message, "\n");
		
		if(1) {
			
			float32_t ret[16];
			uint32_t counter = 0;
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 4.0f;
			for(float32_t g = -range; g < range; g += 1.9f) {
				for(float32_t f = -range; f < range; f += 1.9f) {
					for(float32_t e = -range; e < range; e += 1.9f) {
						for(float32_t d = -range; d < range; d += 1.9f) {
							for(float32_t c = -range; c < range; c += 1.9f) {
								for(float32_t b = -range; b < range; b += 1.9f) {
									for(float32_t a = -range; a < range; a += 0.9f) {
										uint32_t num = Polynomial::sexticNr(a, b, c, d, e, f, g, ret, 1e3f);
										for(uint32_t i = 0; i < num; i++) {
											float32_t x = ret[i];
											float32_t y = x * (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) + g;
											if(abs(y) > 1e0f) TS_LOGF(Error, "sextic32: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d, e, f, g);
											worse = max(worse, abs(y));
											error += abs(y);
											counter += num;
										}
									}
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   sextic32: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float64_t ret[16];
			uint32_t counter = 0;
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 4.0;
			for(float64_t g = -range; g < range; g += 1.9) {
				for(float64_t f = -range; f < range; f += 1.9) {
					for(float64_t e = -range; e < range; e += 1.9) {
						for(float64_t d = -range; d < range; d += 1.9) {
							for(float64_t c = -range; c < range; c += 1.9) {
								for(float64_t b = -range; b < range; b += 1.9) {
									for(float64_t a = -range; a < range; a += 0.9) {
										uint32_t num = Polynomial::sexticNr(a, b, c, d, e, f, g, ret, 1e3);
										for(uint32_t i = 0; i < num; i++) {
											float64_t x = ret[i];
											float64_t y = x * (x * (x * (x * (x * (x * a + b) + c) + d) + e) + f) + g;
											if(abs(y) > 1e-6) TS_LOGF(Error, "sextic64: %u(%u) %16.9f %16.9f : %16.9f %16.9f %16.9f %16.9f %16.9f %16.9f %16.9f\n", i, num, x, y, a, b, c, d, e, f, g);
											worse = max(worse, abs(y));
											error += abs(y);
											counter += num;
										}
									}
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   sextic64: %16.9f / %-16.9f / %u\n", error, worse, counter);
		}
		
		if(1) {
			
			float32_t ret[16];
			float32_t worse = 0.0f;
			float32_t error = 0.0f;
			float32_t range = 5.0f;
			for(float32_t x0 = -range; x0 < range; x0 += 0.9f) {
				if(abs(x0) < 1e-6f) continue;
				for(float32_t x1 = -range; x1 < range; x1 += 0.9f) {
					if(abs(x1) < 1e-6f || x1 < x0 + 1.0f) continue;
					for(float32_t x2 = -range; x2 < range; x2 += 0.9f) {
						if(abs(x2) < 1e-6f || x2 < x1 + 1.0f) continue;
						for(float32_t x3 = -range; x3 < range; x3 += 0.9f) {
							if(abs(x3) < 1e-6f || x3 < x2 + 1.0f) continue;
							for(float32_t x4 = -range; x4 < range; x4 += 0.9f) {
								if(abs(x4) < 1e-6f || x4 < x3 + 1.0f) continue;
								for(float32_t x5 = -range; x5 < range; x5 += 0.09f) {
									if(abs(x5) < 1e-6f || x5 < x4 + 1.0f) continue;
									float32_t b = x0 + x1 + x2 + x3 + x4 + x5;
									float32_t c = x0 * (x1 + x2 + x3 + x4 + x5) + x1 * (x2 + x3 + x4 + x5) + x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5;
									float32_t d = x0 * (x1 * (x2 + x3 + x4 + x5) + x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5) + x1 * (x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5) + x2 * (x3 * (x4 + x5) + x4 * x5) + x3 * x4 * x5;
									float32_t e = x0 * (x1 * (x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5) + x2 * (x3 * (x4 + x5) + x4 * x5) + x3 * x4 * x5) + x1 * (x2 * (x3 * (x4 + x5) + x4 * x5) + x3 * x4 * x5) + x2 * x3 * x4 * x5;
									float32_t f = x0 * (x1 * (x2 * x3 * (x4 + x5) + (x2 * x4 * x5 + x3 * x4 * x5)) + x2 * x3 * x4 * x5) + x1 * x2 * x3 * x4 * x5;
									float32_t g = x0 * x1 * x2 * x3 * x4 * x5;
									uint32_t num = Polynomial::sexticNr(1.0f, -b, c, -d, e, -f, g, ret, 1e3f);
									if(num == 6) {
										worse = max(worse, abs(x0 - ret[0]));
										worse = max(worse, abs(x1 - ret[1]));
										worse = max(worse, abs(x2 - ret[2]));
										worse = max(worse, abs(x3 - ret[3]));
										worse = max(worse, abs(x4 - ret[4]));
										worse = max(worse, abs(x5 - ret[5]));
										error += abs(x0 - ret[0]);
										error += abs(x1 - ret[1]);
										error += abs(x2 - ret[2]);
										error += abs(x3 - ret[3]);
										error += abs(x4 - ret[4]);
										error += abs(x5 - ret[5]);
									} else {
										TS_LOGF(Fatal, "sextic32: %f %f %f %f %f %f : %f %f %f %f %f %f %f : %u\n", x0, x1, x2, x3, x4, x5, 1.0f, -b, c, -d, e, -f, g, num);
									}
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   sextic32: %16.9f / %-16.9f\n", error, worse);
		}
		
		if(1) {
			
			float64_t ret[16];
			float64_t worse = 0.0;
			float64_t error = 0.0;
			float64_t range = 8.0;
			for(float64_t x0 = -range; x0 < range; x0 += 0.9) {
				if(abs(x0) < 1e-6) continue;
				for(float64_t x1 = -range; x1 < range; x1 += 0.9) {
					if(abs(x1) < 1e-6 || x1 < x0 + 1.0) continue;
					for(float64_t x2 = -range; x2 < range; x2 += 0.9) {
						if(abs(x2) < 1e-6 || x2 < x1 + 1.0) continue;
						for(float64_t x3 = -range; x3 < range; x3 += 0.9) {
							if(abs(x3) < 1e-6 || x3 < x2 + 1.0) continue;
							for(float64_t x4 = -range; x4 < range; x4 += 0.9) {
								if(abs(x4) < 1e-6 || x4 < x3 + 1.0) continue;
								for(float64_t x5 = -range; x5 < range; x5 += 0.09) {
									if(abs(x5) < 1e-6 || x5 < x4 + 1.0) continue;
									float64_t b = x0 + x1 + x2 + x3 + x4 + x5;
									float64_t c = x0 * (x1 + x2 + x3 + x4 + x5) + x1 * (x2 + x3 + x4 + x5) + x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5;
									float64_t d = x0 * (x1 * (x2 + x3 + x4 + x5) + x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5) + x1 * (x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5) + x2 * (x3 * (x4 + x5) + x4 * x5) + x3 * x4 * x5;
									float64_t e = x0 * (x1 * (x2 * (x3 + x4 + x5) + x3 * (x4 + x5) + x4 * x5) + x2 * (x3 * (x4 + x5) + x4 * x5) + x3 * x4 * x5) + x1 * (x2 * (x3 * (x4 + x5) + x4 * x5) + x3 * x4 * x5) + x2 * x3 * x4 * x5;
									float64_t f = x0 * (x1 * (x2 * x3 * (x4 + x5) + (x2 * x4 * x5 + x3 * x4 * x5)) + x2 * x3 * x4 * x5) + x1 * x2 * x3 * x4 * x5;
									float64_t g = x0 * x1 * x2 * x3 * x4 * x5;
									uint32_t num = Polynomial::sexticNr(1.0, -b, c, -d, e, -f, g, ret, 1e3);
									if(num == 6) {
										worse = max(worse, abs(x0 - ret[0]));
										worse = max(worse, abs(x1 - ret[1]));
										worse = max(worse, abs(x2 - ret[2]));
										worse = max(worse, abs(x3 - ret[3]));
										worse = max(worse, abs(x4 - ret[4]));
										worse = max(worse, abs(x5 - ret[5]));
										error += abs(x0 - ret[0]);
										error += abs(x1 - ret[1]);
										error += abs(x2 - ret[2]);
										error += abs(x3 - ret[3]);
										error += abs(x4 - ret[4]);
										error += abs(x5 - ret[5]);
									} else {
										TS_LOGF(Fatal, "sextic64: %f %f %f %f %f %f : %f %f %f %f %f %f %f : %u\n", x0, x1, x2, x3, x4, x5, 1.0, -b, c, -d, e, -f, g, num);
									}
								}
							}
						}
					}
				}
			}
			TS_LOGF(Message, "   sextic64: %16.9f / %-16.9f\n", error, worse);
		}
		
		// sextic32:     58.390121460 / 0.193796188      / 521944
		// sextic64:      0.000000107 / 0.000000000      / 516389
		// sextic32:      0.000142753 / 0.000002623
		// sextic64:      0.000000000 / 0.000000000
	}
	
	return 0;
}
