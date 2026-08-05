#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include "reel_forge_uapi.h"
#define DRV_NAME "reel-forge"
#define DRV_VERSION "0.1.0"

struct reel_forge_dev {
    struct platform_device *pdev;
    struct cdev cdev; dev_t devt; struct device *dev; const struct class *class;
};

static int reel_forge_open(struct inode *inode, struct file *filp) {
    filp->private_data = container_of(inode->i_cdev, struct reel_forge_dev, cdev);
    return 0;
}

static long reel_forge_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    struct reel_forge_dev *dev = filp->private_data;
    void __user *u = (void __user *)arg;
    switch (cmd) {
    case REEL_FORGE_IOCTL_START_ENCODE: {
        struct reel_forge_encode_config cfg;
        if (copy_from_user(&cfg, u, sizeof(cfg))) return -EFAULT;
        dev_info(&dev->pdev->dev, "Encode: %s %ux%u %ubps %ufps\n",
            cfg.codec==0?"H264":cfg.codec==1?"H265":"AV1", cfg.width, cfg.height, cfg.bitrate, cfg.fps);
        return 0;
    }
    case REEL_FORGE_IOCTL_STOP_ENCODE: dev_info(&dev->pdev->dev, "Stop encode\n"); return 0;
    case REEL_FORGE_IOCTL_START_DECODE: dev_info(&dev->pdev->dev, "Start decode\n"); return 0;
    case REEL_FORGE_IOCTL_STOP_DECODE: dev_info(&dev->pdev->dev, "Stop decode\n"); return 0;
    case REEL_FORGE_IOCTL_GET_STATUS: { __u32 s=0; if(copy_to_user(u,&s,sizeof(s))) return -EFAULT; return 0; }
    default: return -ENOTTY;
    }
}

static const struct file_operations reel_forge_fops = {
    .owner = THIS_MODULE, .open = reel_forge_open, .unlocked_ioctl = reel_forge_ioctl, .llseek = no_llseek,
};

static int reel_forge_probe(struct platform_device *pdev) {
    struct reel_forge_dev *dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev) return -ENOMEM;
    dev->pdev = pdev; platform_set_drvdata(pdev, dev);
    int ret = alloc_chrdev_region(&dev->devt, 0, 1, DRV_NAME);
    if (ret) return dev_err_probe(&pdev->dev, ret, "chrdev failed\n");
    cdev_init(&dev->cdev, &reel_forge_fops); dev->cdev.owner = THIS_MODULE;
    ret = cdev_add(&dev->cdev, dev->devt, 1);
    if (ret) { unregister_chrdev_region(dev->devt, 1); return ret; }
    dev->dev = device_create(dev->class, &pdev->dev, dev->devt, dev, DRV_NAME "%u", 0);
    if (IS_ERR(dev->dev)) { cdev_del(&dev->cdev); unregister_chrdev_region(dev->devt, 1); return PTR_ERR(dev->dev); }
    dev_info(&pdev->dev, "Reel Forge v%s loaded\n", DRV_VERSION);
    return 0;
}

static void reel_forge_remove(struct platform_device *pdev) {
    struct reel_forge_dev *dev = platform_get_drvdata(pdev);
    device_destroy(dev->class, dev->devt); cdev_del(&dev->cdev); unregister_chrdev_region(dev->devt, 1);
}

static const struct of_device_id reel_forge_of_match[] = {{ .compatible = "nvidia,tegra234-reel-forge" }, {}};
MODULE_DEVICE_TABLE(of, reel_forge_of_match);
static struct platform_driver reel_forge_driver = {
    .probe = reel_forge_probe, .remove = reel_forge_remove,
    .driver = { .name = DRV_NAME, .of_match_table = reel_forge_of_match },
};
static const struct class reel_forge_class = { .name = DRV_NAME, .owner = THIS_MODULE };
static int __init reel_forge_init(void) {
    int r = class_register(&reel_forge_class); if(r)return r;
    r = platform_driver_register(&reel_forge_driver); if(r)class_unregister(&reel_forge_class);
    pr_info("Reel Forge v%s\n", DRV_VERSION); return r;
}
static void __exit reel_forge_exit(void) {
    platform_driver_unregister(&reel_forge_driver); class_unregister(&reel_forge_class);
}
module_init(reel_forge_init); module_exit(reel_forge_exit);
MODULE_AUTHOR("Sandesh <sandesh@soccentric.com>");
MODULE_DESCRIPTION("Jetson AGX Orin video encode/decode driver");
MODULE_LICENSE("GPL v2"); MODULE_VERSION(DRV_VERSION);
