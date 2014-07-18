 File Name:id.c
 File Path: linux/arch/arm/mach-omap2/id.c
 
 
 		break;
+		case 2:
+		/* FALLTHROUGH */
+		default:
+			omap_revision = AM335X_REV_ES2_1;
+			cpu_rev = "2.1";
+			break;
 		}
 		
 		
This check is done in following switch case to verify/add the cpu version.

 		
 		 case 0xb944:
        switch (rev) {
        case 0:
            omap_revision = AM335X_REV_ES1_0;
            cpu_rev = "1.0";
            break;
        case 1:
            omap_revision = AM335X_REV_ES2_0;
            cpu_rev = "2.0";
            break;
        case 2:
        /* FALLTHROUGH */
        default:
            omap_revision = AM335X_REV_ES2_1;
            cpu_rev = "2.1";
            break;
        }
        break;

